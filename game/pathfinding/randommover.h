//
// Created by EgrZver on 05.08.2023.
//
#include <game/types/randommovermodel.h>
#include <game/pathfinding/basepathfinder.h>
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
                    RandomMover(TypesPackage::RandomMoverModel modelType);
                    TypesPackage::Coordinates getNextMove(EntityPackage::Monster* monster, LocationsPackage::Location* location);

            };

            TypesPackage::Coordinates RandomMover::getNextMove(EntityPackage::Monster* monster, LocationsPackage::Location* location) {
                while (true) {
                    std::random_device randomMoverDevice;
                    std::mt19937 RMGenerator(randomMoverDevice());
                    std::uniform_int_distribution<> directionRandomizer(-1, 1);
                    TypesPackage::Coordinates direction{directionRandomizer(RMGenerator),
                                                        directionRandomizer(RMGenerator)};
                    if (this->modelType == TypesPackage::Dumb) {
                        return direction;
                    } else {
                        TypesPackage::Coordinates monsterCoordinates = monster->getCoordinates();
                        if (
                            (monsterCoordinates.x + direction.x < location->getLength()) ||
                            (monsterCoordinates.y + direction.y < location->getHeight()) ||
                            (monsterCoordinates.x + direction.x > 0) ||
                            (monsterCoordinates.y + direction.y > 0)) {
                            LocationsPackage::Tile next = location->getTile(
                                {monsterCoordinates.x + direction.x, monsterCoordinates.y + direction.y});
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
        }
    }
}

#endif //ROGUENGINE_RANDOMMOVER_H
