//
// Created by EgrZver on 25.07.2023.
//
#include <game/locations/tile.h>
#include <game/types/typesPackage.h>
#include <game/entity/entityPackage.h>

#ifndef ROGUENGINE_STRUCTURE_H
#define ROGUENGINE_STRUCTURE_H

namespace RoguEngine {
    namespace GameCore {
        namespace LocationsPackage {
            class Structure {
                private:
                    int height, length;
                    Tile** structureTiles;
                    std::vector<EntityPackage::Entity> structureEntities;
                public:
                    Structure(TypesPackage::Pair size);
                    Tile getTile(TypesPackage::Coordinates coordinates);
                    EntityPackage::Entity getEntityFromPlace(TypesPackage::Coordinates coordinates);
                    int getHeight();
                    int getLength();
                    void setTile(Tile tile, TypesPackage::Coordinates coordinates);
                    void addEntity(EntityPackage::Entity entity);
                    void removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates);
            };

            Structure::Structure(TypesPackage::Pair size) {
                this->height = size.y;
                this->length = size.x;
                this->structureTiles = new Tile* [height];
                for (int i = 0; i < length; i++) {
                    this->structureTiles[i] = new Tile[length];
                }
            }

            Tile Structure::getTile(TypesPackage::Coordinates coordinates) {
                return this->structureTiles[coordinates.y][coordinates.x];
            }

            EntityPackage::Entity Structure::getEntityFromPlace(TypesPackage::Coordinates coordinates) {
                for (int i = 0; i < this->structureEntities.size(); i++) {
                    if (this->structureEntities.at(i).getCoordinates() == coordinates) {
                        return this->structureEntities.at(i);
                    }
                }
                throw std::string("FUCK1234");
            }

            int Structure::getHeight() {
                return this->height;
            }

            int Structure::getLength() {
                return this->length;
            }

            void Structure::setTile(Tile tile, TypesPackage::Coordinates coordinates) {
                this->structureTiles[coordinates.y][coordinates.x] = tile;
            }
            void Structure::addEntity(EntityPackage::Entity entity) {
                this->structureEntities.push_back(entity);
            }
            void Structure::removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates) {
                for (auto it = this->structureEntities.begin(); it != this->structureEntities.end(); it++) {
                    if (it->getCoordinates() == entityCoordinates) {
                        this->structureEntities.erase(it);
                        break;
                    }
                }
            }
        }
    }
}

#endif //ROGUENGINE_STRUCTURE_H
