#ifndef RESOURCE_HPP
#define RESOURCE_HPP
//
#include <string>

class Resource
{
public:
    std::string type;         // Type of resource (e.g., medicine, food, weapons)
    double unfulfilledAmount; // Amount needed but not yet fulfilled

    Resource(std::string type, double unfulfilledAmount) : type(type), unfulfilledAmount(unfulfilledAmount) {}
};

#endif
