//
// Created by EgrZver on 07.08.2023.
//
#include <game/types/coordinates.h>
#include <game/pathfinding/basepathfinder.h>
#include <algorithm>
#include <random>
#include <vector>


#ifndef ROGUENGINE_LINEMOVER_H
#define ROGUENGINE_LINEMOVER_H
/*
namespace RoguEngine {
    namespace GameCore {
        namespace PathfindingPackage {
            class LineMover: public BasePathfinder {
                private:
                    std::vector<TypesPackage::Coordinates> currentPath;
                    TypesPackage::Coordinates sourceCP, destinationCP;
                    std::vector<TypesPackage::Coordinates> AStar(TypesPackage::Coordinates source, TypesPackage::Coordinates destination, int** passMap, TypesPackage::Pair locationSize);
                    std::vector<TypesPackage::Coordinates> buildPath();
                    TypesPackage::Coordinates chooseNode(std::vector<TypesPackage::Coordinates>* reachable, int** passMap);
                    std::vector<TypesPackage::Coordinates> getAdjacent(TypesPackage::Coordinates place, int** passMap, TypesPackage::Pair locationSize);

                public:
                    LineMover(TypesPackage::Coordinates source, TypesPackage::Coordinates destination);
                    void swapSourceDestination();
                    TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) override;

            };

            TypesPackage::Coordinates LineMover::getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) {

            }

            LineMover::LineMover(TypesPackage::Coordinates source, TypesPackage::Coordinates destination) {
                this->sourceCP = source;
                this->destinationCP = destination;
            }

            void LineMover::swapSourceDestination() {
                TypesPackage::Coordinates temp = this->sourceCP;
                this->sourceCP = this->destinationCP;
                this->destinationCP = temp;
            }

            std::vector<TypesPackage::Coordinates> LineMover::AStar(TypesPackage::Coordinates source,
                                                                    TypesPackage::Coordinates destination,
                                                                    int **passMap, TypesPackage::Pair locationSize) {
                std::vector<TypesPackage::Coordinates> reachable = {destination}, explored = {}, path = {};
                while (reachable.size() != 0) {
                    TypesPackage::Coordinates nextTile = chooseNode(&reachable, passMap);
                    path.push_back(nextTile);
                    if (nextTile == this->destinationCP) {
                        return path;
                    }
                    std::remove(reachable.begin(), reachable.end(), nextTile);
                    explored.push_back(nextTile);
                    bool found = false;
                    std::vector<TypesPackage::Coordinates> newReachableRaw = this->getAdjacent(nextTile, passMap, locationSize), newReachable = {};
                    for (int i = 0; i < newReachableRaw.size(); i++) {
                        for (int j = 0; j < explored.size(); j++) {
                            if (newReachableRaw.at(i) == explored.at(j)) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            newReachable.push_back(newReachableRaw.at(i));
                        }
                    }

                    for (int i = 0; i < newReachable.size(); i++) {
                        found = false;
                        for (int j = 0; j < reachable.size(); j++) {
                            if (newReachable.at(i) == reachable.at(j)) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            reachable.push_back(newReachable.at((i)));
                        }

                        if (passMap[nextTile.y][nextTile.x] + 1 < passMap[newReachable.at(i).y][newReachable.at(i).x]) {
                            path.push_back(newReachable.at(i));
                            passMap[newReachable.at(i).y][newReachable.at(i).x] = 0;
                        }
                    }
                }


                for adjacent in new_reachable:
# First time we see this node?
                if adjacent not in reachable:
                reachable.add(adjacent)

# If this is a new path, or a shorter path than what we have, keep it.
                if node.cost + 1 < adjacent.cost:
                adjacent.previous = node
                adjacent.cost = node.cost + 1

# If we get here, no path was found :(
                return None
            }

            auto LineMover::findNode(std::vector<TypesPackage::Coordinates>* where, TypesPackage::Coordinates node) {
                for (auto it = where->begin(); it != where->end(); it++) {
                    if ((*it) == node) {
                        return it;
                    }
                }
            }

            TypesPackage::Coordinates LineMover::chooseNode(std::vector<TypesPackage::Coordinates> *reachable, int** passMap) {
                int minCost = 100000000;
                TypesPackage::Coordinates bestNode = {-1, -1};
                for (int i = 0; i < reachable->size(); i++) {
                    TypesPackage::Coordinates node = reachable->at(i);
                    int startCost = passMap[node.y][node.x],
                        goalCost = sqrt((this->destinationCP.x - this->sourceCP.x)*(this->destinationCP.x - this->sourceCP.x) +
                                        (this->destinationCP.y - this->sourceCP.y)*(this->destinationCP.y - this->sourceCP.y));
                    int totalCost = startCost + goalCost;
                    if (minCost > totalCost) {
                        minCost = totalCost;
                        bestNode = node;
                    }
                }
                return bestNode;
            }

            std::vector<TypesPackage::Coordinates> LineMover::getAdjacent(TypesPackage::Coordinates place,
                                                                          int **passMap,
                                                                          TypesPackage::Pair locationSize) {
                std::vector<TypesPackage::Coordinates> adjacent = {};
                if ((place.x + 1 < locationSize.x) && (place.y + 1 < locationSize.y)) {
                    if (passMap[place.y + 1][place.x + 1] != -1) {
                        adjacent.push_back({place.x + 1, place.y + 1});
                    }
                } else if ((place.x - 1 > -1) && (place.y + 1 < locationSize.y)) {
                    if (passMap[place.y + 1][place.x - 1] != -1) {
                        adjacent.push_back({place.x - 1, place.y + 1});
                    }
                } else if ((place.x + 1 < locationSize.x) && (place.y - 1 > -1)) {
                    if (passMap[place.y - 1][place.x + 1] != -1) {
                        adjacent.push_back({place.x + 1, place.y - 1});
                    }
                } else if ((place.x - 1 > -1) && (place.y - 1 > -1)) {
                    if (passMap[place.y - 1][place.x - 1] != -1) {
                        adjacent.push_back({place.x - 1, place.y - 1});
                    }
                } else if ((place.x + 1 < locationSize.x)) {
                    if (passMap[place.y][place.x + 1] != -1) {
                        adjacent.push_back({place.x + 1, place.y});
                    }
                } else if ((place.x - 1 > -1)) {
                    if (passMap[place.y][place.x - 1] != -1) {
                        adjacent.push_back({place.x - 1, place.y});
                    }
                } else if ((place.y + 1 < locationSize.y)) {
                    if (passMap[place.y + 1][place.x] != -1) {
                        adjacent.push_back({place.x, place.y + 1});
                    }
                } else if ((place.y - 1 > -1)) {
                    if (passMap[place.y - 1][place.x] != -1) {
                        adjacent.push_back({place.x, place.y - 1});
                    }
                }
                return adjacent;
            }
        }
    }
}
 */
#endif //ROGUENGINE_LINEMOVER_H
