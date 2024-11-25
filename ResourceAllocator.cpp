// Definition of the ResourceAllocator class.
// This class manages the allocation of resources to outposts using a fleet of UAVs, 
// ensuring maximum efficiency by prioritizing urgency and minimizing travel time.

#include "ResourceAllocator.hpp"
#include <iostream>
#include <algorithm>

// Constructor for ResourceAllocator.
// Initializes the UAVs and outposts to be managed by the allocator.
ResourceAllocator::ResourceAllocator(std::vector<UAV> uavs, std::vector<Outpost> outposts)
    : uavs(uavs), outposts(outposts) {}

// Main function to allocate resources to outposts using UAVs.
// Implements dynamic prioritization and partial fulfillment logic.
void ResourceAllocator::allocateResources()
{
    // Step 1: Sort outposts based on urgency and distance.
    sortOutposts();

    // Step 2: Iterate through each UAV to allocate resources.
    for (auto &uav : uavs)
    {
        uav.resetCapacity(); // Reset UAV's capacity at the start of each allocation.
        std::cout << "\nUAV " << uav.getId() << " starting allocation:\n";

        bool hasDelivered = false; // Flag to track if the UAV made any deliveries.

        // Step 3: Allocate resources to outposts within UAV's capacity and range.
        for (auto &outpost : outposts)
        {
            // Calculate the total unfulfilled weight of the outpost's requirements.
            double totalUnfulfilledWeight = calculateUnfulfilledWeight(outpost.getRequirements());

            // Skip outposts that are fully fulfilled or out of UAV's range.
            if (totalUnfulfilledWeight <= 0 || outpost.getDistance() > uav.getMaxDistance())
            {
                continue;
            }

            // If UAV can fulfill all requirements, perform full delivery.
            if (totalUnfulfilledWeight <= uav.getAvailableCapacity())
            {
                std::cout << "  Visiting outpost " << outpost.getId() << " (distance: " << outpost.getDistance() << " km) and fulfilling all requirements.\n";
                fulfillResourcesPartially(uav, outpost);
                hasDelivered = true;
            }
            // Otherwise, perform a partial delivery.
            else
            {
                std::cout << "  Visiting outpost " << outpost.getId() << " (distance: " << outpost.getDistance() << " km) for partial fulfillment.\n";
                fulfillResourcesPartially(uav, outpost);
                hasDelivered = true;
                break; // UAV is fully loaded; return to base for reloading.
            }
        }

        // If no deliveries were possible, notify and return UAV to base.
        if (!hasDelivered)
        {
            std::cout << "  No deliveries possible within capacity or range for UAV " << uav.getId() << ". Returning to base.\n";
        }
    }
}

// Helper function to calculate the total unfulfilled weight of resources.
// Iterates through the resources and sums up the unfulfilled amounts.
double ResourceAllocator::calculateUnfulfilledWeight(const std::vector<Resource> &resources)
{
    double totalWeight = 0;
    for (const auto &res : resources)
    {
        totalWeight += res.unfulfilledAmount; // Add unfulfilled amount to total weight.
    }
    return totalWeight;
}

// Function to fulfill resources partially or fully for an outpost.
// Allocates resources to an outpost based on the UAV's available capacity.
void ResourceAllocator::fulfillResourcesPartially(UAV &uav, Outpost &outpost)
{
    // Create a mutable copy of the outpost's requirements.
    auto requirements = outpost.getRequirements();

    // Iterate through each resource in the requirements.
    for (auto &res : requirements)
    {
        if (res.unfulfilledAmount <= 0)
            continue; // Skip resources that are already fulfilled.

        // Fully fulfill the resource if UAV capacity allows.
        if (res.unfulfilledAmount <= uav.getAvailableCapacity())
        {
            std::cout << "  Fulfilling full " << res.unfulfilledAmount << " units of " << res.type << " for outpost " << outpost.getId() << ".\n";
            uav.reduceCapacity(res.unfulfilledAmount);
            res.unfulfilledAmount = 0; // Mark resource as fully fulfilled.
        }
        // Partially fulfill the resource if UAV capacity is insufficient.
        else
        {
            std::cout << "  Partially fulfilling " << uav.getAvailableCapacity() << " units of " << res.type << " for outpost " << outpost.getId() << ".\n";
            res.unfulfilledAmount -= uav.getAvailableCapacity(); // Reduce unfulfilled amount.
            uav.reduceCapacity(uav.getAvailableCapacity());      // Fully load the UAV.
            break;                                               // Stop as UAV is fully loaded.
        }
    }

    // Update the outpost's requirements with the modified values.
    for (size_t i = 0; i < requirements.size(); ++i)
    {
        outpost.getRequirements()[i].unfulfilledAmount = requirements[i].unfulfilledAmount;
    }
}

// Function to sort outposts by urgency and distance.
// Outposts with higher urgency are prioritized, followed by closer distances.
void ResourceAllocator::sortOutposts()
{
    std::sort(outposts.begin(), outposts.end(), [](const Outpost &a, const Outpost &b)
              {
                  if (a.getUrgency() == b.getUrgency())
                      return a.getDistance() < b.getDistance(); // Prioritize closer outposts.
                  return a.getUrgency() > b.getUrgency();       // Prioritize higher urgency.
              });
}
