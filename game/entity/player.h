//
// Created by EgrZver on 21.07.2023.
//
#include <game/types/typesPackage.h>
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
                    TypesPackage::PlayerCharacteristics characteristics{};
                public:
                    Player(std::wstring name, sf::Sprite sprite, int maxHP,  TypesPackage::Coordinates coordinates, int visionRange);
                    int getMaxHP();
            };
            /**
             * \brief Player class constructor
             * \details Standard player constructor. Unlike Entity, Player does not require entityType and symbol because for player it is preset as TypesPackage::EntityType::Player and '@'
             * \param name The name of a player
             * \param sprite The Sprite of a player
             * \param maxHP The max level of HP
             * \param coordinates The start coordinates of a player
             */
            Player::Player(std::wstring name, sf::Sprite sprite, int maxHP, TypesPackage::Coordinates coordinates, int visionRange) : Entity(name, TypesPackage::Player, sprite, coordinates, visionRange) {
                this->characteristics.HP = {maxHP, maxHP};
            }
            /**
             * \brief Max HP getter
             * \details Standard player's max HP getter
             * \return The max HP of a player
             */
            int Player::getMaxHP() {
                return this->characteristics.HP.max;
            }
        }
    }
}

#endif //ROGUENGINE_PLAYER_H
