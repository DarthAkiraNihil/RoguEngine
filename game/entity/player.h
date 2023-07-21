//
// Created by EgrZver on 21.07.2023.
//
#include <game/entity/entity.h>
#include <iostream>

#ifndef ROGUENGINE_PLAYER_H
#define ROGUENGINE_PLAYER_H

namespace RoguEngine {
    namespace GameCore {
        namespace EntityPackage {
            class Player: public Entity {
                private:
                    std::wstring name;
                    AuxiliaryPackage::EntityType entityType;
                    wchar_t symbol;
                    AuxiliaryPackage::Coordinates coordinates;
                    int maxHP;
                public:
                    Player(std::wstring name, int maxHP, AuxiliaryPackage::Coordinates coordinates);
                    int getMaxHP();
            };

            Player::Player(std::wstring name, int maxHP, AuxiliaryPackage::Coordinates coordinates) : Entity(name, AuxiliaryPackage::Player, '@', coordinates) {
                this->maxHP = maxHP;
            }

            int Player::getMaxHP() {
                return this->maxHP;
            }
        }
    }
}

#endif //ROGUENGINE_PLAYER_H
