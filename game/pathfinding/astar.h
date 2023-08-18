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
            /**
             * \brief Main pathfinder
             * \details This is the class purpose of which is pathfinding in a location that is assigned to the class.
             * Actually should be used only in a path generator.
             */
            class AStarPathfinder {
                private:
                    TypesPackage::Pair locationSize{};
                    TypesPackage::AStarGraphNode** locationGraph;
                    bool hasAssigned;

                    void buildGraph(int** passMap, TypesPackage::Pair size);
                    std::vector<TypesPackage::Coordinates> buildPath(TypesPackage::AStarGraphNode* goal);
                    TypesPackage::Coordinates chooseNode(std::vector<TypesPackage::Coordinates> *reachable, TypesPackage::Coordinates destination);

                    void releaseGraph();

                public:
                    AStarPathfinder();
                    ~AStarPathfinder();
                    void assignLocation(int** passMap, TypesPackage::Pair size);
                    void clearPathfindingCache();
                    std::vector<TypesPackage::Coordinates> findPath(TypesPackage::Coordinates source, TypesPackage::Coordinates destination);
            };

            /**
             * \brief Standard class constructor
             * \details Actually this is like a default constructor but I think that it had to be defined explicitly
             */
            AStarPathfinder::AStarPathfinder() {
                this->hasAssigned = false;
                this->locationGraph = nullptr;
                this->locationSize = {-1, -1};
            }

            /**
             * \brief Standard class destructor
             * \details Releases location graph assigned to the finder if the class had it.
             */
            AStarPathfinder::~AStarPathfinder() {
                if (this->hasAssigned) {
                    this->releaseGraph();
                }
            }

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


            /**
             * \brief Location assigner
             * \details If the pathfinder has an assigned location the class releases the graph at first, but in all cases the class builds a location graph according to the pass map
             * \param passMap The pointer to the pass map of a location
             * \param size The size of the pass map
             */
            void AStarPathfinder::assignLocation(int **passMap, TypesPackage::Pair size) {
                if (this->hasAssigned) {
                    this->releaseGraph();
                    this->hasAssigned = false;
                }
                this->buildGraph(passMap, size);
                this->hasAssigned = true;
            }

            /**
             * \brief Cache cleaner
             * \details Sets costs of all location graph nodes to zero, and the pointers to the previous node to nullptr.
             * Does nothing if the class had no assigned location.
             * Should be called after finding a path using findPath
             */
            void AStarPathfinder::clearPathfindingCache() {
                if (this->hasAssigned) {
                    for (int i = 0; i < this->locationSize.y; i++) {
                        for (int j = 0; j < this->locationSize.x; j++) {
                            if (this->locationGraph[i][j].cost != -1) {
                                this->locationGraph[i][j].cost = 0;
                                this->locationGraph[i][j].previous = nullptr;
                            }
                        }
                    }
                }
            }

            /**
             * \brief The function to find the path
             * \details This method is used, as its name says, to find a path between two points of a location.
             * Uses A* (AStar) algorithm for it:
             * -# Creates vectors of reachable (with source node in it) and explored nodes
             * -# While vector of reachable is not empty, the method does these actions:
             *  -# Chooses a node from the reachable nodes that is the most near to the destination (chooseNode method)
             *  -# If chooses the destination then builds the path (buildPath method) according to the pointers to the previous nodes
             *  -# Removes the found node from the reachable and adds in to the explored
             *  -# Finds all adjacent nodes for the current node that are not explored
             *  -# For all found adjacent nodes, if the cost of an adjacent node is 0 (a new path) or greater than the cost of the current node (a shorter path) then updates
             *  the cost of the adjacent node and assigns the previous node as the current one.
             * -# If no path has been found then returns an empty vector
             * \param source The coordinates of the path source
             * \param destination The coordinates of the path destination
             * \return The vector of directions in which an entity should go to reach the destination point, or an empty vector if no path has been found
             * \throw NoAssignedLocationException if the pathfinder has no assigned location
             */
            std::vector<TypesPackage::Coordinates> AStarPathfinder::findPath(TypesPackage::Coordinates source, TypesPackage::Coordinates destination) {
                if (!this->hasAssigned) {
                    throw CoreExceptions::NoAssignedLocationException("A location has not been assigned to the pathfinder, nowhere to find");
                }
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
                        for (int j = -1; j < 2; j++) { // yes, this is necessary to write the conditions so
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
                    //int startCost = this->locationGraph[node.y][node.x].cost,
                    //    goalCost = (int) std::sqrt(std::pow(destination.x - node.y, 2) + std::pow(destination.y - node.y, 2));
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

            void AStarPathfinder::releaseGraph() {
                for (int i = 0; i < this->locationSize.y; i++) {
                    delete [] this->locationGraph[i];
                }
                delete [] this->locationGraph;
            }

        }
    }
}

#endif //ROGUENGINE_ASTAR_H
