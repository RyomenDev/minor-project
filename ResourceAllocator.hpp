// Declaration of the ResourceAllocator class.

#ifndef RESOURCEALLOCATOR_HPP
#define RESOURCEALLOCATOR_HPP

#include <vector>
#include "UAV.hpp"
#include "Outpost.hpp"

class ResourceAllocator
{
private:
    std::vector<UAV> uavs;         // List of UAVs
    std::vector<Outpost> outposts; // List of outposts

public:
    ResourceAllocator(std::vector<UAV> uavs, std::vector<Outpost> outposts);
    void allocateResources();

private:
    double calculateUnfulfilledWeight(const std::vector<Resource> &resources);
    void fulfillResourcesPartially(UAV &uav, Outpost &outpost);
    void sortOutposts();
};

#endif
