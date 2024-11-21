#include "Outpost.hpp"
//

Outpost::Outpost(int id, double distance, int urgency)
    : id(id), distance(distance), urgency(urgency) {}

int Outpost::getId() const
{
    return id;
}

double Outpost::getDistance() const
{
    return distance;
}

int Outpost::getUrgency() const
{
    return urgency;
}

void Outpost::addResource(const Resource &res)
{
    resources.push_back(res);
}

std::vector<Resource> &Outpost::getRequirements()
{
    return resources; // Mutable reference
}

const std::vector<Resource> &Outpost::getRequirements() const
{
    return resources; // Immutable reference
}
