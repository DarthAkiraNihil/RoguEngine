//
// Created by EgrZver on 20.07.2023.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game/types/typesPackage.h"

#ifndef ROGUENGINE_ENTITY_H
#define ROGUENGINE_ENTITY_H

namespace RoguEngine {
    namespace GameCore {
        namespace EntityPackage {
            /**
             * \brief Base entity class
             * \details Represents a basic class for all entities.
             * Contains all variables that are common for all characters such as name, symbol etc.
             * Name, type and sprite of an entity are immutable
             */
            class Entity {
                public:
                    Entity(std::wstring name, TypesPackage::EntityType entityType, sf::Sprite sprite, TypesPackage::Coordinates coordinates);
                    std::wstring getName();
                    TypesPackage::EntityType getType();
                    sf::Sprite getSprite();
                    TypesPackage::Coordinates getCoordinates();
                    void setCoordinates(TypesPackage::Coordinates newCoordinates);
                    void move(TypesPackage::Coordinates direction);
                private:
                    std::wstring name;
                    TypesPackage::EntityType entityType;
                    sf::Sprite sprite;
                    //wchar_t symbol;
                    TypesPackage::Coordinates coordinates;

            };
            /**
             * \brief Entity class constructor
             * \details Standard entity constructor
             * \param name The name of an entity
             * \param entityType The type of an entity
             * \param symbol The symbol of an entity. Will be used in rendering
             * \param coordinates The start coordinates of an entity
             */
            Entity::Entity(std::wstring name, TypesPackage::EntityType entityType, sf::Sprite sprite, TypesPackage::Coordinates coordinates) {
                this->name = name;
                this->entityType = entityType;
                this->sprite = sprite;
                this->coordinates = coordinates;
            }
            /**
             * \brief Name getter
             * \details Standard entity's name getter
             * \return The name of an entity
             */
            std::wstring Entity::getName() {
                return this->name;
            }
            /**
             * \brief Sprite getter
             * \details Standard entity's sprite getter
             * \return The sprite of an entity
             */
            sf::Sprite Entity::getSprite() {
                return this->sprite;
            }
            /**
             * \brief Type getter
             * \details Standard entity's type getter
             * \return The type of an entity
             */
            TypesPackage::EntityType Entity::getType() {
                return this->entityType;
            }
            /**
             * \brief Coordinates getter
             * \details Standard entity's coordinates getter
             * \return The coordinates of an entity
             */
            TypesPackage::Coordinates Entity::getCoordinates() {
                return this->coordinates;
            }
            /**
             * \brief Coordinates setter
             * \details Standard entity's name setter
             * \param newCoordinates New coordinates of an entity
             */
            void Entity::setCoordinates(TypesPackage::Coordinates newCoordinates) {
                this->coordinates = newCoordinates;
            }

            /**
             * \brief Entity mover
             * \details Changes entity's coordinates according to the direction
             * \param direction Direction to move
             */
            void Entity::move(TypesPackage::Coordinates direction) {
                this->coordinates.x += direction.x;
                this->coordinates.y += direction.y;
            }
        }
    }
}
#endif //ROGUENGINE_ENTITY_H
