//
// Created by EgrZver on 07.08.2023.
//
#include <game/types/astargraphnode.h>

#ifndef ROGUENGINE_ASTAR_H
#define ROGUENGINE_ASTAR_H

namespace RoguEngine {
    namespace GameCore {
        namespace PathfindingPackage {
            class AStarPathfinder {
                private:
                    TypesPackage::Pair locationSize;

                public:
                    AStarPathfinder(int** passMap, TypesPackage::Pair locationSize);
                    TypesPackage::AStarGraphNode** locationGraph;
            };

            AStarPathfinder::AStarPathfinder(int **passMap, TypesPackage::Pair locationSize) {
                this->locationGraph = new TypesPackage::AStarGraphNode* [locationSize.y];
                for (int i = 0; i < locationSize.y; i++) {
                    this->locationGraph[i] = new TypesPackage::AStarGraphNode [locationSize.x];
                    for (int j = 0; j < locationSize.x; j++) {
                        this->locationGraph[i][j].coordinates = {j, i};
                        this->locationGraph[i][j].cost = passMap[i][j];
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
        }
    }
}

#endif //ROGUENGINE_ASTAR_H
