//
// Created by EgrZver on 05.08.2023.
//
#include <game/types/randommovermodel.h>
#include <game/pathfinding/basepathfinder.h>
#include <game/locations/location.h>
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
                    TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, LocationsPackage::Location* location) override;

            };

            TypesPackage::Coordinates RandomMover::getNextMove(TypesPackage::Coordinates source, LocationsPackage::Location* location) {
                while (true) {
                    std::random_device randomMoverDevice;
                    std::mt19937 RMGenerator(randomMoverDevice());
                    std::uniform_int_distribution<> directionRandomizer(-1, 1);
                    TypesPackage::Coordinates direction{directionRandomizer(RMGenerator),
                                                        directionRandomizer(RMGenerator)};
                    if (this->modelType == TypesPackage::Dumb) {
                        return direction;
                    } else {
                        if (
                            (source.x + direction.x < location->getLength()) ||
                            (source.y + direction.y < location->getHeight()) ||
                            (source.x + direction.x > 0) ||
                            (source.y + direction.y > 0)) {
                            LocationsPackage::Tile next = location->getTile(
                                {source.x + direction.x, source.y + direction.y});
                            if (next.isPassable()) {
                                return direction;
                            } else {
                                continue;
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

#endif //ROGUENGINE_RANDOMMOVER_H
