//
// Created by EgrZver on 09.08.2023.
//
#include <vector>
#include <random>
#include <game/types/coordinates.h>
#include <game/pathfinding/astar.h>

#ifndef ROGUENGINE_PATHGENERATOR_H
#define ROGUENGINE_PATHGENERATOR_H

namespace RoguEngine {
    namespace GameCore {
        namespace PathfindingPackage {
            class PathGenerator {
                private:
                    int** passMap;
                    TypesPackage::Pair passMapSize;
                    AStarPathfinder pathfinder;
                public:
                    void assignLocation(int** locationPassMap, TypesPackage::Pair locationSize);
                    std::vector<TypesPackage::Coordinates> generateRandomDirectionDumb(TypesPackage::Coordinates source);
                    std::vector<TypesPackage::Coordinates> generateSinglePath(TypesPackage::Coordinates source, TypesPackage::Coordinates destination);
                    //std::vector<TypesPackage::Coordinates> generatePathWithRandomDestination(TypesPackage::Coordinates source);
            };

            void PathGenerator::assignLocation(int **locationPassMap, TypesPackage::Pair locationSize) {
                this->passMapSize = locationSize;
                this->pathfinder.assignLocation(locationPassMap, locationSize);
            }

            std::vector<TypesPackage::Coordinates> PathGenerator::generateRandomDirectionDumb(
                TypesPackage::Coordinates source) {
                std::random_device randomMoverDevice;
                std::mt19937 RMGenerator(randomMoverDevice());
                std::uniform_int_distribution<> directionRandomizer(-1, 1);
                while (true) {
                    TypesPackage::Coordinates direction{directionRandomizer(RMGenerator),
                                                        directionRandomizer(RMGenerator)};
                    if (direction.x == 0 && direction.y == 0) {
                        continue;
                    } else {
                        if (
                            (source.x + direction.x < passMapSize.x) &&
                            (source.y + direction.y < passMapSize.y) &&
                            (source.x + direction.x > -1) &&
                            (source.y + direction.y > -1)) {
                            return {direction};
                        } else {
                            continue;
                        }
                    }
                }
            }

            std::vector<TypesPackage::Coordinates>
            PathGenerator::generateSinglePath(TypesPackage::Coordinates source, TypesPackage::Coordinates destination) {
                std::vector<TypesPackage::Coordinates> path = this->pathfinder.findPath(source, destination);
                std::cout << "path len " << path.size() << std::endl;
                this->pathfinder.clearCosts();
                return path;
            }
        }
    }
}

#endif //ROGUENGINE_PATHGENERATOR_H
