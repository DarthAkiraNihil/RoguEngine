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
                    int pathLen;
                    bool foundPathStatus;

                public:
                    LineMover(TypesPackage::Coordinates source, TypesPackage::Coordinates destination);
                    void swapSourceDestination();
                    TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) override;
                    void addPathStep(TypesPackage::Coordinates step);
                    void clearPath();
                    bool getFindPathStatus();
                    bool setPathAsFound();
                    TypesPackage::Coordinates getSource();
                    TypesPackage::Coordinates getDestination();

            };

            TypesPackage::Coordinates LineMover::getNextMove(TypesPackage::Coordinates source, int **passMap,
                                                             TypesPackage::Pair locationSize) {
                if (!this->foundPathStatus) {
                    AStarPathfinder pathfinder(passMap, locationSize);
                    if (!this->currentPath.empty()) this->currentPath.clear();
                    this->currentPath = pathfinder.findPath(this->sourceCP, this->destinationCP);
                    this->iterator = this->currentPath.rbegin();
                    this->foundPathStatus = true;
                    return *(this->iterator);
                } else {
                    if (this->iterator == this->currentPath.rend()) {
                        foundPathStatus = false;
                        return {0, 0};
                    }
                }
            }

            void LineMover::swapSourceDestination() {
                TypesPackage::Coordinates temp = this->sourceCP;
                this->sourceCP = this->destinationCP;
                this->destinationCP = this->sourceCP;
            }

            LineMover::LineMover(TypesPackage::Coordinates source, TypesPackage::Coordinates destination) {
                this->sourceCP = source;
                this->destinationCP = destination;
                this->pathLen = 0;
            }


            void LineMover::addPathStep(TypesPackage::Coordinates step) {
                this->currentPath.push_back(step);
                this->pathLen++;
            }

            void LineMover::clearPath() {
                if (!this->currentPath.empty()) {
                    this->currentPath.clear();
                }
            }

            TypesPackage::Coordinates LineMover::getSource() {
                return this->sourceCP;
            }

            TypesPackage::Coordinates LineMover::getDestination() {
                return this->destinationCP;
            }
        }
    }
}

#endif //ROGUENGINE_LINEMOVER_H
