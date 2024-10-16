# UAV Resource Allocation System

This project models an Unmanned Aerial Vehicle (UAV) resource allocation system to optimize the delivery of essential resources (medicine, food, and weapons) to various outposts. The system takes into account multiple UAVs with varying capacities, distances, and time constraints, ensuring maximum efficiency in resource distribution.

## Overview

The system allocates resources based on the following:

- **Resource priorities** (medicine, food, and weapons with fixed priority levels)
- **UAV constraints** (capacity, distance, and time per trip)
- **Outpost requests** (amount and urgency)

The goal is to maximize resource delivery, minimize travel time, and efficiently manage UAV capacities.

## Model Breakdown

### Key Structures

1. **UAV Struct**

   - **Attributes**: Each UAV has specific load capacity, maximum distance it can travel, and a time limit per trip.
   - **Functionality**: UAVs are assigned to outposts based on their ability to meet resource requirements within their capacity and distance constraints.

2. **Resource Struct**

   - **Attributes**: Resources include medicine, food, and weapons, each with a fixed priority (medicine being the highest).
   - **Allocation**: Resources are allocated based on both the outposts' requests and the UAVs' carrying capacities.

3. **Outpost Struct**
   - **Attributes**: Outposts specify their distance, the required amount of resources, and the urgency of the request.
   - **Functionality**: The system prioritizes outposts based on urgency and distance, ensuring the most urgent deliveries are made first.

## Core Logic and Features

### Dynamic Prioritization

Outposts are prioritized based on urgency first and distance second. This ensures that the most critical outposts receive resources quickly, while minimizing travel time for UAVs.

### Resource Types with Fixed Priorities

Resources are prioritized as follows:

- **Medicine**: Highest priority
- **Food**: Medium priority
- **Weapons**: Lowest priority

The system ensures that medicine is delivered first when possible, followed by food and then weapons.

### UAV Allocation

UAVs are assigned based on:

- **Capacity**: Ensuring the UAV can carry the required resources.
- **Distance**: Only UAVs within a certain distance range are assigned to minimize unnecessary trips.

### Maximizing Delivery Efficiency

The system tries to assign each UAV to deliver resources to as many outposts as possible within its capacity and distance limits. If a UAV cannot fulfill the full request of an outpost, it delivers what it can and keeps track of the remaining resources for future trips.

### Partial Fulfillment

In cases where a UAV cannot carry all requested resources in one trip, it will deliver partial amounts and return to the base to reload, reducing idle time and ensuring that resources are delivered as quickly as possible.

### Route Optimization

Outposts with equal urgency are served based on their proximity. This ensures that UAVs visit the closest outposts first, minimizing travel time and fuel consumption.

### Advanced Time Management

Multiple UAVs work concurrently. If a UAV cannot complete a full delivery due to capacity or distance limitations, it will return to the base, reload, and resume deliveries. This concurrency reduces idle time and maximizes the delivery efficiency.

### Default UAV Table

The system uses a predefined table (`defaultUAVs`) containing the following attributes for each UAV:

- `id`
- `loadCapacity`
- `maxDistance`
- `timePerTrip`

This table simulates the UAV data coming from an external source and allows for simplified input.

## Folder/File Structure

The project follows a modular design, with separate files for each component:

```bash
UAV_Resource_Allocation/
│
├── include/
│   ├── UAV.h                 # UAV class declaration
│   ├── Outpost.h             # Outpost class and Resource struct declaration
│   ├── ResourceAllocator.h   # ResourceAllocator class declaration
│
├── src/
│   ├── UAV.cpp               # UAV class definition
│   ├── Outpost.cpp           # Outpost class definition
│   ├── ResourceAllocator.cpp # ResourceAllocator class definition
│
└── main.cpp                  # Main logic and program flow

```

## Key OOP Concepts Used

### Encapsulation

The details of UAVs, outposts, and resource allocation are encapsulated in their respective classes, ensuring clean, maintainable code.

### Modularity

The code is split into distinct modules (UAV, Outpost, ResourceAllocator), which allows for easy management and future expansion of the project.

### Separation of Concerns

The main logic (resource allocation) is abstracted into a dedicated ResourceAllocator class, which handles all the resource distribution calculations, keeping the codebase organized and easy to understand.

## How to Use

```
clang++ -std=c++20 main.cpp UAV.cpp Outpost.cpp ResourceAllocator.cpp -o main
```

**Input:** The system takes as input the number of outposts and their resource requirements.
**UAV Data:** UAV information is pre-loaded from the default UAV table (defaultUAVs).
**Output:** The system outputs a detailed plan of resource allocation, including which UAVs are assigned to which outposts and how much of each resource is delivered.
