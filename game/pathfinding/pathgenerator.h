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
                    std::vector<TypesPackage::Coordinates> generateRandomDirectionRational(TypesPackage::Coordinates source);
                    std::vector<TypesPackage::Coordinates> generateSinglePath(TypesPackage::Coordinates source, TypesPackage::Coordinates destination);
                    std::vector<TypesPackage::Coordinates> generatePathToRandomPointEverywhere(TypesPackage::Coordinates source);
                    std::vector<TypesPackage::Coordinates> generatePathToRandomPointRadial(TypesPackage::Coordinates source, int outerCircleRadius, int innerCircleRadius);
                    std::vector<TypesPackage::Coordinates> generateDirectionToTarget(TypesPackage::Coordinates source, TypesPackage::Coordinates target);
                    //std::vector<TypesPackage::Coordinates> generatePathWithRandomDestination(TypesPackage::Coordinates source);
            };

            void PathGenerator::assignLocation(int **locationPassMap, TypesPackage::Pair locationSize) {
                this->passMapSize = locationSize;
                this->passMap = locationPassMap;
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
                this->pathfinder.clearPathfindingCache();
                return path;
            }

            std::vector<TypesPackage::Coordinates>
            PathGenerator::generateRandomDirectionRational(TypesPackage::Coordinates source) {
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
                                if (this->passMap[source.y + direction.y][source.x + direction.x] != -1) return {direction};
                                continue;
                            } else {
                                continue;
                            }
                        }
                    }
            }

            std::vector<TypesPackage::Coordinates>
            PathGenerator::generatePathToRandomPointEverywhere(TypesPackage::Coordinates source) {
                std::random_device randomDeviceX, randomDeviceY;
                std::mt19937 xGen(randomDeviceX()), yGen(randomDeviceY());
                std::uniform_int_distribution<> xRandomizer(0, this->passMapSize.x - 1), yRandomizer(0, this->passMapSize.y - 1);
                TypesPackage::Coordinates rndDest{};
                while (true) {
                    rndDest = {xRandomizer(xGen), yRandomizer(yGen)};
                    if (rndDest == source || this->passMap[rndDest.y][rndDest.x] == -1) {
                        continue;
                    } else {
                        std::vector<TypesPackage::Coordinates> path = this->generateSinglePath(source, rndDest);
                        if (!path.empty()) {
                            return path;
                        }
                        continue;
                    }
                }
            }

            std::vector<TypesPackage::Coordinates>
            PathGenerator::generatePathToRandomPointRadial(TypesPackage::Coordinates source,
                                                           int outerCircleRadius,
                                                           int innerCircleRadius) {
                std::random_device randomDeviceX, randomDeviceY;
                std::mt19937 xGen(randomDeviceX()), yGen(randomDeviceY());
                std::uniform_int_distribution<> xRandomizer((source.x - outerCircleRadius) > -1 ? source.x - outerCircleRadius : 0,
                                                            (source.x + outerCircleRadius) < this->passMapSize.x ? source.x + outerCircleRadius : this->passMapSize.x - 1),
                                                yRandomizer((source.y - outerCircleRadius) > -1 ? source.y - outerCircleRadius : 0,
                                                            (source.x + outerCircleRadius) < this->passMapSize.y ? source.x + outerCircleRadius : this->passMapSize.y - 1);
                TypesPackage::Coordinates rndDest{};
                while (true) {
                    rndDest = {xRandomizer(xGen), yRandomizer(yGen)};
                    int distance = (int) std::sqrt(std::pow(rndDest.x, 2) + std::pow(rndDest.y, 2));
                    if (rndDest == source || this->passMap[rndDest.y][rndDest.x] == -1 || !((distance <= outerCircleRadius) || (distance >= innerCircleRadius))) {
                        continue;
                    } else {
                        std::vector<TypesPackage::Coordinates> path = this->generateSinglePath(source, rndDest);
                        if (!path.empty()) {
                            return path;
                        }
                        continue;
                    }
                }
            }

            std::vector<TypesPackage::Coordinates>
            PathGenerator::generateDirectionToTarget(TypesPackage::Coordinates source,
                                                      TypesPackage::Coordinates target) {
                std::vector<TypesPackage::Coordinates> path = this->generateSinglePath(source, target);
                return {path[0]};
            }
        }
    }
}

#endif //ROGUENGINE_PATHGENERATOR_H
