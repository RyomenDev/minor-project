// Definition of the ResourceAllocator class.

#include "ResourceAllocator.hpp"
#include <iostream>
#include <algorithm>

ResourceAllocator::ResourceAllocator(std::vector<UAV> uavs, std::vector<Outpost> outposts)
    : uavs(uavs), outposts(outposts) {}

void ResourceAllocator::allocateResources()
{
    // Sort outposts before allocating
    sortOutposts();

    // Iterate through each UAV and allocate resources
    for (auto &uav : uavs)
    {
        uav.resetCapacity(); // Reset available capacity for each UAV
        std::cout << "\nUAV " << uav.getId() << " starting allocation:\n";

        bool hasDelivered = false;

        // Try to serve as many outposts as possible within UAV's capacity and distance
        for (auto &outpost : outposts)
        {
            double totalUnfulfilledWeight = calculateUnfulfilledWeight(outpost.getResources());

            if (totalUnfulfilledWeight <= 0 || outpost.getDistance() > uav.getMaxDistance())
            {
                continue; // Skip if fully fulfilled or outpost is out of UAV's range
            }

            if (totalUnfulfilledWeight <= uav.getAvailableCapacity())
            {
                std::cout << "  Visiting outpost " << outpost.getId() << " (distance: " << outpost.getDistance() << " km) and fulfilling all requirements.\n";
                fulfillResourcesPartially(uav, outpost); // Fully fulfill
                hasDelivered = true;
            }
            else
            {
                std::cout << "  Visiting outpost " << outpost.getId() << " (distance: " << outpost.getDistance() << " km) for partial fulfillment.\n";
                fulfillResourcesPartially(uav, outpost); // Partially fulfill
                hasDelivered = true;
                break; // UAV is fully loaded, return to base to reload
            }
        }

        if (!hasDelivered)
        {
            std::cout << "  No deliveries possible within capacity or range for UAV " << uav.getId() << ". Returning to base.\n";
        }
    }
}

double ResourceAllocator::calculateUnfulfilledWeight(const std::vector<Resource> &resources)
{
    double totalWeight = 0;
    for (const auto &res : resources)
    {
        totalWeight += res.unfulfilledAmount; // Unfulfilled amount contributes to weight
    }
    return totalWeight;
}

void ResourceAllocator::fulfillResourcesPartially(UAV &uav, Outpost &outpost)
{
    // Create a mutable copy of the requirements
    auto requirements = outpost.getRequirements();

    for (auto &res : requirements)
    {
        if (res.unfulfilledAmount <= 0)
            continue; // Skip fulfilled resources

        if (res.unfulfilledAmount <= uav.getAvailableCapacity())
        {
            std::cout << "  Fulfilling full " << res.unfulfilledAmount << " units of " << res.type << " for outpost " << outpost.getId() << ".\n";
            uav.reduceCapacity(res.unfulfilledAmount);
            res.unfulfilledAmount = 0; // Fully fulfilled
        }
        else
        {
            std::cout << "  Partially fulfilling " << uav.getAvailableCapacity() << " units of " << res.type << " for outpost " << outpost.getId() << ".\n";
            res.unfulfilledAmount -= uav.getAvailableCapacity(); // Partially fulfilled
            uav.reduceCapacity(uav.getAvailableCapacity());      // UAV fully loaded
            break;                                               // UAV cannot carry more in this trip
        }
    }

    // Update the outpost's requirements after modification
    for (size_t i = 0; i < requirements.size(); ++i)
    {
        outpost.getRequirements()[i].unfulfilledAmount = requirements[i].unfulfilledAmount;
    }
}

void ResourceAllocator::sortOutposts()
{
    std::sort(outposts.begin(), outposts.end(), [](const Outpost &a, const Outpost &b)
              {
                  if (a.getUrgency() == b.getUrgency())
                      return a.getDistance() < b.getDistance(); // Closest first
                  return a.getUrgency() > b.getUrgency();       // Higher urgency first
              });
}
