//
// Created by EgrZver on 05.08.2023.
//
//#include <game/pathfinding/randommover.h>
#include <iostream>
#include <game/types/typesPackage.h>
#include <game/entity/entity.h>
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
                    TypesPackage::MoverType moverType;
                public:
                    Monster(std::wstring name, sf::Sprite sprite, int maxHP,  TypesPackage::Coordinates coordinates, TypesPackage::MoverType moverType);
                    int getMaxHP();
                    TypesPackage::MoverType getMoverType();
            };

            Monster::Monster(std::wstring name, sf::Sprite sprite, int maxHP, TypesPackage::Coordinates coordinates, TypesPackage::MoverType moverType) : Entity(name, TypesPackage::Monster, sprite, coordinates) {
                this->characteristics.HP = {maxHP, maxHP};
                this->moverType = moverType;
            }

            int Monster::getMaxHP() {
                return this->characteristics.HP.max;
            }

            TypesPackage::MoverType Monster::getMoverType() {
                return this->moverType;
            }
        }
    }
}

#endif //ROGUENGINE_MONSTER_H
