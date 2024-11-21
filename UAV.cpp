// Definition of the UAV class.
//
#include "UAV.hpp"

UAV::UAV(int id, double loadCapacity, double maxDistance)
    : id(id), loadCapacity(loadCapacity), availableCapacity(loadCapacity), maxDistance(maxDistance) {}

int UAV::getId() const
{
    return id;
}

double UAV::getAvailableCapacity() const
{
    return availableCapacity;
}

double UAV::getMaxDistance() const
{
    return maxDistance;
}

void UAV::reduceCapacity(double amount)
{
    availableCapacity -= amount;
}

void UAV::resetCapacity()
{
    availableCapacity = loadCapacity; // Reset capacity to maximum load
}
