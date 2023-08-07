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
            struct AStarGraphNode {
                int cost;
                std::vector<Coordinates> adjacent;
                Coordinates coordinates;
                AStarGraphNode* previous;
            };
        }
    }
}

#endif //ROGUENGINE_ASTARGRAPHNODE_H
