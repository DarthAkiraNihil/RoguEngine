//
// Created by EgrZver on 05.08.2023.
//
//#include <game/pathfinding/randommover.h>
#include <iostream>
#include <game/types/typesPackage.h>
#include <game/entity/entity.h>
#include <game/pathfinding/basepathfinder.h>
//

#ifndef ROGUENGINE_MONSTER_H
#define ROGUENGINE_MONSTER_H

namespace RoguEngine {
    namespace GameCore {
        namespace EntityPackage {
            class Monster: public Entity {
                private:
                    std::wstring name;
                    TypesPackage::EntityType entityType;
                    sf::Sprite sprite;
                    TypesPackage::Coordinates coordinates;
                    TypesPackage::MonsterCharacteristics characteristics;
                    PathfindingPackage::BasePathfinder* mover;
                    //TypesPackage::MoverType moverType;
                public:
                    Monster(std::wstring name, sf::Sprite sprite, int maxHP,  TypesPackage::Coordinates coordinates, PathfindingPackage::BasePathfinder* mover);
                    int getMaxHP();
                    TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize);
            };

            Monster::Monster(std::wstring name, sf::Sprite sprite, int maxHP, TypesPackage::Coordinates coordinates, PathfindingPackage::BasePathfinder* mover) : Entity(name, TypesPackage::Monster, sprite, coordinates) {
                this->characteristics.HP = {maxHP, maxHP};
                this->mover = mover;
            }

            int Monster::getMaxHP() {
                return this->characteristics.HP.max;
            }

            TypesPackage::Coordinates Monster::getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) {
                return this->mover->getNextMove(source, passMap, locationSize);
            }

        }
    }
}

#endif //ROGUENGINE_MONSTER_H
