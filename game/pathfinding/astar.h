//
// Created by EgrZver on 07.08.2023.
//
#include <cmath>
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

                    void buildGraph(int** passMap, TypesPackage::Pair size);
                    std::vector<TypesPackage::Coordinates> buildPath(TypesPackage::AStarGraphNode* goal);
                    TypesPackage::Coordinates chooseNode(std::vector<TypesPackage::Coordinates> *reachable, TypesPackage::Coordinates destination);

                public:
                    ~AStarPathfinder();
                    void assignLocation(int** passMap, TypesPackage::Pair size);
                    void clearCosts();
                    std::vector<TypesPackage::Coordinates> findPath(TypesPackage::Coordinates source, TypesPackage::Coordinates destination);
            };

            void AStarPathfinder::buildGraph(int **passMap, TypesPackage::Pair size) {
                this->locationGraph = new TypesPackage::AStarGraphNode* [size.y];
                for (int i = 0; i < size.y; i++) {
                    this->locationGraph[i] = new TypesPackage::AStarGraphNode [size.x];
                    for (int j = 0; j < size.x; j++) {
                        this->locationGraph[i][j].coordinates = {j, i};
                        this->locationGraph[i][j].cost = passMap[i][j];
                        this->locationGraph[i][j].previous = nullptr;
                    }
                }

                this->locationSize = size;
            }

            AStarPathfinder::~AStarPathfinder() {
                for (int i = 0; i < this->locationSize.y; i++) {
                    delete [] this->locationGraph[i];
                }
                delete [] this->locationGraph;
            }

            void AStarPathfinder::assignLocation(int **passMap, TypesPackage::Pair size) {
                this->buildGraph(passMap, size);
            }

            void AStarPathfinder::clearCosts() {
                for (int i = 0; i < this->locationSize.y; i++) {
                    for (int j = 0; j < this->locationSize.x; j++) {
                        if (this->locationGraph[i][j].cost != -1) {
                            this->locationGraph[i][j].cost = 0;
                            this->locationGraph[i][j].previous = nullptr; // TODO FIX ADJACENT SEARCHING
                        }
                    }
                }
            }

            std::vector<TypesPackage::Coordinates> AStarPathfinder::findPath(TypesPackage::Coordinates source, TypesPackage::Coordinates destination) {
                std::vector<TypesPackage::Coordinates> reachable = {source}, explored = {};
                while (!reachable.empty()) {
                    TypesPackage::Coordinates node = this->chooseNode(&reachable, destination);
                    if (node == destination) {
                        return buildPath(&(this->locationGraph[destination.y][destination.x]));
                    }

                    auto it = std::find(reachable.begin(), reachable.end(), node);
                    if (it != reachable.end()) reachable.erase(it);
                    explored.push_back(node);

                    std::vector<TypesPackage::Coordinates> newReachableRaw = {}, newReachable = {};
                    for (int i = -1; i < 2; i++) {
                        for (int j = -1; j < 2; j++) {
                            if (i != 0 || j != 0) {
                                if ((node.x + i < this->locationSize.x) &&
                                    (node.x + i > -1) &&
                                    (node.y + j < this->locationSize.y) &&
                                    (node.y + j > -1)) {
                                    if (this->locationGraph[node.y + j][node.x + i].cost != -1) newReachableRaw.push_back({node.x + i, node.y + j});
                                }
                            }
                        }
                    }
                    for (TypesPackage::Coordinates & adjacent: newReachableRaw) {
                        std::cout << fmt::format("Adjacent node: x: {}, y: {}", adjacent.x, adjacent.y) << std::endl;
                    }
                    std::cout << "END" << std::endl;
                    //for (TypesPackage::Coordinates & adjacent: this->getAdjacentNodes(node)) {
                    //    newReachableRaw.push_back(adjacent);
                    //}

                    for (TypesPackage::Coordinates & rawReachable: newReachableRaw) {
                        bool found = std::find(explored.begin(), explored.end(), rawReachable) != explored.end();
                        if (!found) newReachable.push_back(rawReachable);
                    }

                    for (TypesPackage::Coordinates & adjacent: newReachable) {
                        bool found = std::find(reachable.begin(), reachable.end(), adjacent) != reachable.end();
                        if (!found) {
                            reachable.push_back(adjacent);
                        }

                        if ((this->locationGraph[node.y][node.x].cost + 1 < this->locationGraph[adjacent.y][adjacent.x].cost) || (this->locationGraph[adjacent.y][adjacent.x].cost == 0)) {
                            this->locationGraph[adjacent.y][adjacent.x].previous = &(this->locationGraph[node.y][node.x]);
                            this->locationGraph[adjacent.y][adjacent.x].cost = this->locationGraph[node.y][node.x].cost + 1;
                        }
                    }

                    for (int i = 0; i < 25; i++) {
                        for (int j = 0; j < 25; j++) {
                            std::cout << this->locationGraph[i][j].cost << " ";
                        }
                        std::cout << std::endl;
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

            TypesPackage::Coordinates AStarPathfinder::chooseNode(std::vector<TypesPackage::Coordinates> *reachable, TypesPackage::Coordinates destination) {
                int minCost = 10000000; TypesPackage::Coordinates bestNode = {-1, -1};
                for (TypesPackage::Coordinates & node: *reachable) {
                    int startCost = this->locationGraph[node.y][node.x].cost,
                        goalCost = abs(destination.x - node.x) +
                                            abs(destination.y - node.y);
                    if (minCost > startCost + goalCost) {
                        minCost = startCost + goalCost;
                        bestNode = node;
                    }
                }
                return bestNode;
            }

        }
    }
}

#endif //ROGUENGINE_ASTAR_H
