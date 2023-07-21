//
// Created by EgrZver on 21.07.2023.
//
#include <game/locations/tile.h>
#include "game/types/typesPackage.h"
#include <game/entity/entity.h>
#include <include/conio21/conio2.h>
#include <iostream>
#include <vector>

#ifndef ROGUENGINE_LOCATION_H
#define ROGUENGINE_LOCATION_H

namespace RoguEngine {
    namespace GameCore {
        namespace LocationsPackage {
            class Location {
                private:
                    int height, length;
                    Tile** locationMap;
                    std::vector<EntityPackage::Entity> locationEntities;
                public:
                    Location(int height, int length);
                    Tile getTile(TypesPackage::Coordinates coordinates);
                    EntityPackage::Entity getEntityFromPlace(TypesPackage::Coordinates coordinates);
                    void moveEntity(TypesPackage::Coordinates oldCoordinates, TypesPackage::Coordinates newCoordinates);
                    int getHeight();
                    int getLength();
                    void setTile(Tile tile, TypesPackage::Coordinates coordinates);
                    void addEntity(EntityPackage::Entity entity);
                    void removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates);
                    void render(TypesPackage::Coordinates placeToRender);
            };

            Location::Location(int height, int length) {
                this->height = height;
                this->length = length;
                this->locationMap = new Tile* [height];
                for (int i = 0; i < length; i++) {
                    this->locationMap[i] = new Tile[length];
                }
            }

            Tile Location::getTile(TypesPackage::Coordinates coordinates) {
                return this->locationMap[coordinates.y][coordinates.x];
            }

            EntityPackage::Entity Location::getEntityFromPlace(TypesPackage::Coordinates coordinates) {
                for (int i = 0; i < this->locationEntities.size(); i++) {
                    if (this->locationEntities.at(i).getCoordinates() == coordinates) {
                        return this->locationEntities.at(i);
                    }
                }
                throw std::string("FUCK1234");
            }

            int Location::getHeight() {
                return this->height;
            }

            int Location::getLength() {
                return this->length;
            }

            void Location::moveEntity(TypesPackage::Coordinates oldCoordinates, TypesPackage::Coordinates newCoordinates) {
                for (int i = 0; i < this->locationEntities.size(); i++) {
                    if (this->locationEntities.at(i).getCoordinates() == oldCoordinates) {
                        this->locationEntities.at(i).setCoordinates(newCoordinates);
                        break;
                    }
                }
            }
            void Location::setTile(Tile tile, TypesPackage::Coordinates coordinates) {
                this->locationMap[coordinates.y][coordinates.x] = tile;
            }
            void Location::addEntity(EntityPackage::Entity entity) {
                this->locationEntities.push_back(entity);
            }
            void Location::removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates) {
                for (auto it = this->locationEntities.begin(); it != this->locationEntities.end(); it++) {
                    if (it->getCoordinates() == entityCoordinates) {
                        this->locationEntities.erase(it);
                        break;
                    }
                }
            }
            void Location::render(TypesPackage::Coordinates placeToRender) {
                for (int i = 0; i < this->height; i++) {
                    for (int j = 0; j < this->length; j++) {
                        gotoxy(placeToRender.x + j + 1, placeToRender.y + i + 1);
                        std::wcout << this->locationMap[i][j].getChar();
                    }
                }
                for (int i = 0; i < this->locationEntities.size(); i++) {
                    EntityPackage::Entity temp = this->locationEntities.at(i);
                    gotoxy(temp.getCoordinates().x + 1, temp.getCoordinates().y + 1);
                    std::wcout << temp.getSymbol();
                }
            }

        }
    }
}

#endif //ROGUENGINE_LOCATION_H
