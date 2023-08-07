//
// Created by EgrZver on 07.08.2023.
//
#include <game/types/coordinates.h>
#include <game/pathfinding/basepathfinder.h>
#include <game/pathfinding/astar.h>
#include <algorithm>
#include <random>
#include <vector>


#ifndef ROGUENGINE_LINEMOVER_H
#define ROGUENGINE_LINEMOVER_H

namespace RoguEngine {
    namespace GameCore {
        namespace PathfindingPackage {
            class LineMover: public BasePathfinder {
                private:
                    std::vector<TypesPackage::Coordinates> currentPath;
                    TypesPackage::Coordinates sourceCP, destinationCP;
                    std::vector<TypesPackage::Coordinates>::reverse_iterator iterator;
                    bool foundPathStatus;

                public:
                    LineMover(TypesPackage::Coordinates source, TypesPackage::Coordinates destination);
                    void swapSourceDestination();
                    TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) override;

            };

            TypesPackage::Coordinates LineMover::getNextMove(TypesPackage::Coordinates source, int **passMap,
                                                             TypesPackage::Pair locationSize) {
                if (!this->foundPathStatus) {
                    AStarPathfinder pathfinder(passMap, locationSize);
                    this->currentPath.clear();
                    this->currentPath = pathfinder.findPath(this->sourceCP, this->destinationCP);
                    this->iterator = this->currentPath.rbegin();
                    this->foundPathStatus = true;
                    return *this->iterator;
                } else {
                    if (this->iterator == this->currentPath.rend()) {
                        foundPathStatus = false;
                    }
                }
            }



        }
    }
}

#endif //ROGUENGINE_LINEMOVER_H
