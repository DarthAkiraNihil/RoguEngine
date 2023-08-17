//
// Created by EgrZver on 07.08.2023.
//
#include <vector>
#include <game/types/coordinates.h>

#ifndef ROGUENGINE_ASTARGRAPHNODE_H
#define ROGUENGINE_ASTARGRAPHNODE_H

namespace RoguEngine {
    namespace GameCore {
        namespace TypesPackage {
            /**
             * \brief Location graph node
             * \details Represents a node of a location graph that is used inA* (AStar) pathfinding algorithm.
             * Contains the cost, the coordinates and the pointer to the previous node of a node.
             * The pointer is used in pathfinding to build a path.
             */
            struct AStarGraphNode {
                /// The cost of a node
                int cost;
                /// The Coordinates of a node
                Coordinates coordinates;
                /// The pointer to the previous node in pathfinding
                AStarGraphNode* previous;
            };
        }
    }
}

#endif //ROGUENGINE_ASTARGRAPHNODE_H
