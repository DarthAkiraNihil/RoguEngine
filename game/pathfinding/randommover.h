//
// Created by EgrZver on 05.08.2023.
//
#include <game/types/randommovermodel.h>
#include <game/pathfinding/basepathfinder.h>
//#include <game/locations/location.h>
#include <random>

#ifndef ROGUENGINE_RANDOMMOVER_H
#define ROGUENGINE_RANDOMMOVER_H

namespace RoguEngine {
    namespace GameCore {
        namespace PathfindingPackage {
            class RandomMover: public BasePathfinder {
                private:
                    TypesPackage::RandomMoverModel modelType;
                public:
                    explicit RandomMover(TypesPackage::RandomMoverModel modelType);
                    TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) override;
                    TypesPackage::MoverType getMoverType() override;

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

            TypesPackage::MoverType RandomMover::getMoverType() {
                return TypesPackage::Random;
            }
        }
    }
}

#endif //ROGUENGINE_RANDOMMOVER_H
