//
// Created by EgrZver on 21.07.2023.
//
#include <game/locations/tile.h>
#include <game/auxiliary/auxiliary.h>
#include <game/entity/entity.h>
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
                    Tile getTile(AuxiliaryPackage::Coordinates coordinates);
                    EntityPackage::Entity getEntityFromPlace(AuxiliaryPackage::Coordinates coordinates);
                    void moveEntity(AuxiliaryPackage::Coordinates oldCoordinates, AuxiliaryPackage::Coordinates newCoordinates);
                    void setTile(Tile tile, AuxiliaryPackage::Coordinates coordinates);
                    void addEntity(EntityPackage::Entity entity);
                    void removeEntityFromPlace(AuxiliaryPackage::Coordinates entityCoordinates);
                    void render(AuxiliaryPackage::Coordinates placeToRender);
            };

            Location::Location(int height, int length) {
                this->height = height;
                this->length = length;
                this->locationMap = new Tile* [height];
                for (int i = 0; i < length; i++) {
                    this->locationMap[i] = new Tile[length];
                }
            }

            Tile Location::getTile(AuxiliaryPackage::Coordinates coordinates) {
                return this->locationMap[coordinates.y][coordinates.x];
            }

            EntityPackage::Entity Location::getEntityFromPlace(AuxiliaryPackage::Coordinates coordinates) {
                for (int i = 0; i < this->locationEntities.size(); i++) {
                    if (this->locationEntities.at(i).getCoordinates() == coordinates) {
                        return this->locationEntities.at(i);
                    }
                }
                throw std::string("FUCK1234");
            }

            void Location::moveEntity(AuxiliaryPackage::Coordinates oldCoordinates, AuxiliaryPackage::Coordinates newCoordinates) {
                for (int i = 0; i < this->locationEntities.size(); i++) {
                    if (this->locationEntities.at(i).getCoordinates() == oldCoordinates) {
                        this->locationEntities.at(i).setCoordinates(newCoordinates);
                        break;
                    }
                }
            }
            void Location::setTile(Tile tile, AuxiliaryPackage::Coordinates coordinates) {
                this->locationMap[coordinates.y][coordinates.x] = tile;
            }
            void Location::addEntity(EntityPackage::Entity entity) {
                this->locationEntities.push_back(entity);
            }
            void Location::removeEntityFromPlace(AuxiliaryPackage::Coordinates entityCoordinates) {
                for (auto it = this->locationEntities.begin(); it != this->locationEntities.end(); it++) {
                    if (it->getCoordinates() == entityCoordinates) {
                        this->locationEntities.erase(it);
                        break;
                    }
                }
            }
            void Location::render(AuxiliaryPackage::Coordinates placeToRender) {

            }

        }
    }
}

#endif //ROGUENGINE_LOCATION_H
