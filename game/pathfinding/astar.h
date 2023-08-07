//
// Created by EgrZver on 07.08.2023.
//
#include <vector>
#include <algorithm>
#include <game/types/astargraphnode.h>

#ifndef ROGUENGINE_ASTAR_H
#define ROGUENGINE_ASTAR_H

namespace RoguEngine {
    namespace GameCore {
        namespace PathfindingPackage {
            class AStarPathfinder {
                private:
                    TypesPackage::Pair locationSize;
                    TypesPackage::AStarGraphNode** locationGraph;
                    std::vector<TypesPackage::Coordinates> buildPath(TypesPackage::AStarGraphNode* goal);
                    TypesPackage::AStarGraphNode chooseNode(std::vector<TypesPackage::AStarGraphNode> *reachable, TypesPackage::Coordinates destination);
                    std::vector<TypesPackage::AStarGraphNode> getAdjacentNodes(std::vector<TypesPackage::Coordinates> nodesCoordinates);

                public:
                    AStarPathfinder(int** passMap, TypesPackage::Pair locationSize);
                    std::vector<TypesPackage::Coordinates> findPath(TypesPackage::Coordinates source, TypesPackage::Coordinates destination);
            };

            AStarPathfinder::AStarPathfinder(int **passMap, TypesPackage::Pair locationSize) {
                this->locationGraph = new TypesPackage::AStarGraphNode* [locationSize.y];
                for (int i = 0; i < locationSize.y; i++) {
                    this->locationGraph[i] = new TypesPackage::AStarGraphNode [locationSize.x];
                    for (int j = 0; j < locationSize.x; j++) {
                        this->locationGraph[i][j].coordinates = {j, i};
                        this->locationGraph[i][j].cost = passMap[i][j];
                        this->locationGraph[i][j].previous = nullptr;
                    }
                }

                for (int i = 0; i < locationSize.y; i++) {
                    for (int j = 0; j < locationSize.x; j++) {
                        if (i > 0) {
                            if (passMap[i - 1][j] != -1) {
                                this->locationGraph[i][j].adjacent.push_back({j, i - 1});
                            }
                        }
                        if (i < locationSize.y - 1) {
                            if (passMap[i + 1][j] != -1) {
                                this->locationGraph[i][j].adjacent.push_back({j, i + 1});
                            }
                        }
                        if (j > 0) {
                            if (i > 0) {
                                if (passMap[i - 1][j - 1] != -1) {
                                    this->locationGraph[i][j].adjacent.push_back({j - 1, i - 1});
                                }
                            }
                            if (i < locationSize.y - 1) {
                                if (passMap[i + 1][j - 1] != -1) {
                                    this->locationGraph[i][j].adjacent.push_back({j - 1, i + 1});
                                }
                            }
                            if (passMap[i][j - 1] != -1) {
                                this->locationGraph[i][j].adjacent.push_back({j - 1, i});
                            }
                        }
                        if (j < locationSize.x - 1) {
                            if (i > 0) {
                                if (passMap[i - 1][j + 1] != -1) {
                                    this->locationGraph[i][j].adjacent.push_back({j + 1, i - 1});
                                }
                            }
                            if (i < locationSize.y - 1) {
                                if (passMap[i + 1][j + 1] != -1) {
                                    this->locationGraph[i][j].adjacent.push_back({j + 1, i + 1});
                                }
                            }
                            if (passMap[i][j + 1] != -1) {
                                this->locationGraph[i][j].adjacent.push_back({j + 1, i});
                            }
                        }
                    }
                }

                this->locationSize = locationSize;
            }

            std::vector<TypesPackage::Coordinates>
            AStarPathfinder::findPath(TypesPackage::Coordinates source, TypesPackage::Coordinates destination) {
                std::vector<TypesPackage::AStarGraphNode> reachable = {this->locationGraph[source.y][source.y]}, explored = {};

                while (!reachable.empty()) {
                    TypesPackage::AStarGraphNode node = this->chooseNode(&reachable, source);
                    if (node.coordinates == destination) {
                        return buildPath(&this->locationGraph[destination.y][destination.x]);
                    }

                    for (auto it = reachable.begin(); it != reachable.end(); it++) {
                        if ((*it).coordinates == node.coordinates) {
                            reachable.erase(it);
                            break;
                        }
                    }
                    explored.push_back(node);

                    std::vector<TypesPackage::AStarGraphNode> newReachableRaw = this->getAdjacentNodes(node.adjacent), newReachable;
                    for (int i = 0; i < newReachableRaw.size(); i++) {
                        bool found = false;
                        for (int j = 0; j < explored.size(); j++) {
                            if (explored.at(j).coordinates == newReachableRaw.at(i).coordinates) {
                                found = true;
                                break;
                            }
                        }

                        if (!found) {
                            reachable.push_back(newReachable.at(i));
                        }
                    }

                    for (int i = 0; i < newReachable.size(); i++) {
                        bool found = false;
                        for (int j = 0; j < reachable.size(); j++) {
                            if (reachable.at(j).coordinates == newReachable.at(i).coordinates) {
                                found = true;
                                break;
                            }
                        }

                        if (!found) {
                            reachable.push_back(newReachable.at(i));
                        }

                        if (node.cost + 1 < newReachable.at(i).cost) {
                            newReachable[i].previous = &node;
                            newReachable[i].cost = node.cost + 1;
                        }
                    }
                }

                return {};
            }

            std::vector<TypesPackage::Coordinates> AStarPathfinder::buildPath(TypesPackage::AStarGraphNode *goal) {

                std::vector<TypesPackage::Coordinates> path;
                while (goal->previous != nullptr) {
                    TypesPackage::Coordinates previousCoordinates = goal->previous->coordinates;
                    path.push_back({goal->coordinates.x - previousCoordinates.x, goal->coordinates.y - previousCoordinates.y});
                    goal = goal->previous;
                }
                return path;
            }

            TypesPackage::AStarGraphNode AStarPathfinder::chooseNode(std::vector<TypesPackage::AStarGraphNode> *reachable, TypesPackage::Coordinates destination) {
                int minCost = 10000000; TypesPackage::AStarGraphNode bestNode;
                for (int i = 0; i < reachable->size(); i++) {
                    int startCost = reachable->at(i).cost,
                        goalCost = int(sqrt((destination.x - reachable->at(i).coordinates.x)*(destination.x - reachable->at(i).coordinates.x) +
                                        (destination.y - reachable->at(i).coordinates.y)*(destination.y - reachable->at(i).coordinates.y)));
                    if (minCost > startCost + goalCost) {
                        minCost = startCost + goalCost;
                        bestNode = reachable->at(i);
                    }
                }
                return bestNode;
            }

            std::vector<TypesPackage::AStarGraphNode>
            AStarPathfinder::getAdjacentNodes(std::vector<TypesPackage::Coordinates> nodesCoordinates) {
                std::vector<TypesPackage::AStarGraphNode> nodes;
                for (int i = 0; i < nodesCoordinates.size(); i++) {
                    TypesPackage::Coordinates nodeCoordinates = nodesCoordinates.at(i);
                    nodes.push_back(this->locationGraph[nodeCoordinates.y][nodeCoordinates.x]);
                }
                return nodes;
            }
        }
    }
}

#endif //ROGUENGINE_ASTAR_H
