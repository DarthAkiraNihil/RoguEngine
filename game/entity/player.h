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
            /**
             * \brief Player entity class
             * \details Represents a class of a player.
             * Contains some specific variables and methods such as HP etc.
             */
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
            /**
             * \brief Player class constructor
             * \details Standard player constructor. Unlike Entity, Player does not require entityType and symbol because for player it is preset as AuxiliaryPackage::EntityType::Player and '@'
             * \param name The name of a player
             * \param maxHP The max level of HP
             * \param coordinates The start coordinates of a player
             */
            Player::Player(std::wstring name, int maxHP, AuxiliaryPackage::Coordinates coordinates) : Entity(name, AuxiliaryPackage::Player, '@', coordinates) {
                this->maxHP = maxHP;
            }
            /**
             * \brief Max HP getter
             * \details Standard player's max HP getter
             * \return The max HP of a player
             */
            int Player::getMaxHP() {
                return this->maxHP;
            }
        }
    }
}

#endif //ROGUENGINE_PLAYER_H
