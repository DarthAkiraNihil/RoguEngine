//
// Created by EgrZver on 05.08.2023.
//
#include <iostream>
#include <game/types/typesPackage.h>
#include <game/entity/entity.h>

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
                public:
                    Monster(std::wstring name, sf::Sprite sprite, int maxHP,  TypesPackage::Coordinates coordinates);
                    int getMaxHP();
            };

            Monster::Monster(std::wstring name, sf::Sprite sprite, int maxHP, TypesPackage::Coordinates coordinates) : Entity(name, TypesPackage::Player, sprite, coordinates) {
                this->characteristics.HP = {maxHP, maxHP};
            }

            int Monster::getMaxHP() {
                return this->characteristics.HP.max;
            }
        }
    }
}

#endif //ROGUENGINE_MONSTER_H
