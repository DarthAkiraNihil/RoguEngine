//
// Created by EgrZver on 20.07.2023.
//
#include <iostream>
#include <game/auxiliary/auxiliary.h>

#ifndef ROGUENGINE_ENTITY_H
#define ROGUENGINE_ENTITY_H

class Entity {
    public:
        Entity(std::wstring name, EntityType entityType, wchar_t symbol, Coordinates coordinates);
        std::wstring getName();
        EntityType getType();
        wchar_t getSymbol();
        Coordinates getCoordinates();
        void setCoordinates(Coordinates newCoordinates);
    private:
        std::wstring name;
        EntityType entityType;
        wchar_t symbol;
        Coordinates coordinates;

};

Entity::Entity(std::wstring name, EntityType entityType, wchar_t symbol, Coordinates coordinates) {
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

EntityType Entity::getType() {
    return this->entityType;
}

Coordinates Entity::getCoordinates() {
    return this->coordinates;
}

void Entity::setCoordinates(Coordinates newCoordinates) {
    this->coordinates = newCoordinates;
}

#endif //ROGUENGINE_ENTITY_H
