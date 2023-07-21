//
// Created by EgrZver on 20.07.2023.
//
#include <iostream>
#include <game/auxiliary/auxiliary.h>

#ifndef ROGUENGINE_ENTITY_H
#define ROGUENGINE_ENTITY_H

namespace RoguEngine {
    namespace GameCore {
        namespace EntityPackage {
            /**
             * \brief Base entity class
             * \details Represents a basic class for all entities.
             * Contains all variables that are common for all characters such as name, symbol etc.
             * Name, type and symbol of an entity are immutable
             */
            class Entity {
                public:
                    Entity(std::wstring name, AuxiliaryPackage::EntityType entityType, wchar_t symbol, AuxiliaryPackage::Coordinates coordinates);
                    std::wstring getName();
                    AuxiliaryPackage::EntityType getType();
                    wchar_t getSymbol();
                    AuxiliaryPackage::Coordinates getCoordinates();
                    void setCoordinates(AuxiliaryPackage::Coordinates newCoordinates);
                private:
                    std::wstring name;
                    AuxiliaryPackage::EntityType entityType;
                    wchar_t symbol;
                    AuxiliaryPackage::Coordinates coordinates;

            };
            /**
             * \brief Entity class constructor
             * \details Standard entity constructor
             * \param name The name of an entity
             * \param entityType The type of an entity
             * \param symbol The symbol of an entity. Will be used in rendering
             * \param coordinates The start coordinates of an entity
             */
            Entity::Entity(std::wstring name, AuxiliaryPackage::EntityType entityType, wchar_t symbol, AuxiliaryPackage::Coordinates coordinates) {
                this->name = name;
                this->entityType = entityType;
                this->symbol = symbol;
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
             * \brief Symbol getter
             * \details Standard entity's symbol getter
             * \return The symbol of an entity
             */
            wchar_t Entity::getSymbol() {
                return this->symbol;
            }
            /**
             * \brief Type getter
             * \details Standard entity's type getter
             * \return The type of an entity
             */
            AuxiliaryPackage::EntityType Entity::getType() {
                return this->entityType;
            }
            /**
             * \brief Coordinates getter
             * \details Standard entity's coordinates getter
             * \return The coordinates of an entity
             */
            AuxiliaryPackage::Coordinates Entity::getCoordinates() {
                return this->coordinates;
            }
            /**
             * \brief Coordinates setter
             * \details Standard entity's name setter
             * \param newCoordinates New coordinates of an entity
             */
            void Entity::setCoordinates(AuxiliaryPackage::Coordinates newCoordinates) {
                this->coordinates = newCoordinates;
            }
        }
    }
}
#endif //ROGUENGINE_ENTITY_H
