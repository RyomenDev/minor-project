
// Declaration of the UAV class.

#ifndef UAV_HPP
#define UAV_HPP

class UAV
{
private:
    int id;                   // Unique identifier for the UAV
    double loadCapacity;      // Maximum load capacity of the UAV
    double availableCapacity; // Current available capacity
    double maxDistance;       // Maximum distance the UAV can travel

public:
    UAV(int id, double loadCapacity, double maxDistance);

    int getId() const;
    double getAvailableCapacity() const;
    double getMaxDistance() const;
    void reduceCapacity(double amount);
    void resetCapacity();
};

#endif
