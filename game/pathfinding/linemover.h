//
// Created by EgrZver on 07.08.2023.
//
#include <game/types/coordinates.h>
#include <game/pathfinding/basepathfinder.h>
#include <vector>


#ifndef ROGUENGINE_LINEMOVER_H
#define ROGUENGINE_LINEMOVER_H

namespace RoguEngine {
    namespace GameCore {
        namespace PathfindingPackage {
            class LineMover: public BasePathfinder {
                private:
                    std::vector<TypesPackage::Coordinates> path;
                    TypesPackage::Coordinates sourceCP, destinationCP;
                public:
                    explicit RandomMover(TypesPackage::RandomMoverModel modelType);
                    TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) override;

            };

            TypesPackage::Coordinates RandomMover::getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) {
                while (true) {
                    std::random_device randomMoverDevice;
                    std::mt19937 RMGenerator(randomMoverDevice());
                    std::uniform_int_distribution<> directionRandomizer(-1, 1);
                    TypesPackage::Coordinates direction{directionRandomizer(RMGenerator),
                                                        directionRandomizer(RMGenerator)};
                    if (direction.x == 0 && direction.y == 0) {
                        continue;
                    } else {
                        if (
                            (source.x + direction.x < locationSize.x) &&
                            (source.y + direction.y < locationSize.y) &&
                            (source.x + direction.x > -1) &&
                            (source.y + direction.y > -1)) {
                            switch (this->modelType) {
                                case TypesPackage::Dumb: {
                                    return direction;
                                }
                                case TypesPackage::Rational: {
                                    if (passMap[source.y + direction.y][source.x + direction.x] != -1 ){
                                        return direction;
                                    } else {
                                        continue;
                                    }
                                }
                            }

                        } else {
                            continue;
                        }
                    }
                }
            }

            RandomMover::RandomMover(TypesPackage::RandomMoverModel modelType) {
                this->modelType = modelType;
            }
        }
    }
}
#endif //ROGUENGINE_LINEMOVER_H
