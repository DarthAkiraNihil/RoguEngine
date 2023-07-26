//
// Created by EgrZver on 21.07.2023.
//
#include <game/locations/tile.h>
#include <game/types/typesPackage.h>
#include <game/locations/structure.h>
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
                    Location(TypesPackage::Pair size);
                    Tile getTile(TypesPackage::Coordinates coordinates);
                    EntityPackage::Entity getEntityFromPlace(TypesPackage::Coordinates coordinates);
                    int getHeight();
                    int getLength();
                    void setTile(Tile tile, TypesPackage::Coordinates coordinates);
                    void addEntity(EntityPackage::Entity entity);
                    void removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates);
                    void pasteStructure(Structure structure, TypesPackage::Coordinates at);
            };

            Location::Location(TypesPackage::Pair size) {
                this->height = size.y;
                this->length = size.x;
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

            void Location::pasteStructure(Structure structure, TypesPackage::Coordinates at) {
                for (int i = 0; i < structure.getHeight(); i++) {
                    for (int j = 0; j < structure.getLength(); j++) {

                        this->locationMap[at.y + i][at.x + j] = structure.getTile({j, i});
                    }
                }
            }

        }
    }
}

#endif //ROGUENGINE_LOCATION_H
