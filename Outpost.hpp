#ifndef OUTPOST_HPP
#define OUTPOST_HPP

#include <vector>
#include "Resource.hpp"

class Outpost
{
private:
    int id;                          // Unique identifier for the outpost
    double distance;                 // Distance from the base station
    int urgency;                     // Urgency level of the resource request
    std::vector<Resource> resources; // Resources requested by the outpost

public:
    Outpost(int id, double distance, int urgency);

    int getId() const;
    double getDistance() const;
    int getUrgency() const;
    void addResource(const Resource &res);

    std::vector<Resource> &getRequirements();             // Mutable reference
    const std::vector<Resource> &getRequirements() const; // Immutable reference
};

#endif
