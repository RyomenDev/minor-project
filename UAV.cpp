// Definition of the UAV class.
// The UAV class represents an unmanned aerial vehicle with attributes such as ID, 
// load capacity, and maximum travel distance. It includes methods to manage its 
// capacity during resource allocation tasks.

#include "UAV.hpp"

// Constructor for the UAV class.
// Initializes the UAV with a unique ID, maximum load capacity, and maximum distance.
UAV::UAV(int id, double loadCapacity, double maxDistance)
    : id(id), loadCapacity(loadCapacity), availableCapacity(loadCapacity), maxDistance(maxDistance) {}

// Getter for the UAV's ID.
// Returns the unique identifier of the UAV.
int UAV::getId() const
{
    return id;
/*************  ✨ Codeium Command ⭐  *************/
/// \brief Returns the maximum distance the UAV can travel.
///
/// This is a measure of how far the UAV can travel in one trip.
///
/// \return The maximum distance (in kilometers) the UAV can travel.
/******  29545967-6670-4c96-8e48-aaa6895d7cad  *******/}

// Getter for the UAV's available capacity.
// Returns the remaining capacity of the UAV after resource allocation.
double UAV::getAvailableCapacity() const
{
    return availableCapacity;
}

// Getter for the UAV's maximum distance.
// Returns the maximum distance the UAV can travel on a single trip.
double UAV::getMaxDistance() const
{
    return maxDistance;
}

// Reduces the UAV's available capacity by a specified amount.
// Used during resource allocation to track utilized capacity.
void UAV::reduceCapacity(double amount)
{
    availableCapacity -= amount;
}

// Resets the UAV's available capacity to its maximum load.
// Typically called after a trip is completed and the UAV is ready for a new allocation.
void UAV::resetCapacity()
{
    availableCapacity = loadCapacity;
}
