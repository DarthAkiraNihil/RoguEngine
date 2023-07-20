//
// Created by EgrZver on 20.07.2023.
//
#include <iostream>
#include <game/auxiliary/auxiliary.h>

#ifndef ROGUENGINE_ENTITY_H
#define ROGUENGINE_ENTITY_H
namespace RoguEngine {
    namespace GameModule {
        namespace EntityPackage {
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

            Entity::Entity(std::wstring name, AuxiliaryPackage::EntityType entityType, wchar_t symbol, AuxiliaryPackage::Coordinates coordinates) {
                this->name = name;
                this->entityType = entityType;
                this->symbol = symbol;
                this->coordinates = coordinates;
            }

            std::wstring Entity::getName() {
                return this->name;
            }

            wchar_t Entity::getSymbol() {
                return this->symbol;
            }

            AuxiliaryPackage::EntityType Entity::getType() {
                return this->entityType;
            }

            AuxiliaryPackage::Coordinates Entity::getCoordinates() {
                return this->coordinates;
            }

            void Entity::setCoordinates(AuxiliaryPackage::Coordinates newCoordinates) {
                this->coordinates = newCoordinates;
            }
        }
    }
}
#endif //ROGUENGINE_ENTITY_H
