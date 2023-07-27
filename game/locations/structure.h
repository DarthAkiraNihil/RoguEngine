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
            /**
             * \brief Structure class
             * \details A class that represents a game Structure. Contains only one layer of tiles.
             * Also stores information about all entities in the Structure. A structure can be pasted in here.
             */
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

            /**
             * \brief Structure class constructor
             * \details Standard Structure class constructor
             * \param size The size of the Structure (length x height)
             */
            Structure::Structure(TypesPackage::Pair size) {
                this->height = size.y;
                this->length = size.x;
                this->structureTiles = new Tile* [height];
                for (int i = 0; i < length; i++) {
                    this->structureTiles[i] = new Tile[length];
                }
            }

            /**
             * \brief Structure tile getter
             * \details Standard Structure tile getter
             * \param coordinates The coordinates of a tile
             * \return The tile of a Structure on desired coordinates
             */
            Tile Structure::getTile(TypesPackage::Coordinates coordinates) {
                return this->structureTiles[coordinates.y][coordinates.x];
            }

            /**
             * \brief Structure entity getter
             * \details Standard Structure entity getter
             * \param coordinates The coordinates of an entity
             * \return The entity of a Structure on desired coordinates
             */
            EntityPackage::Entity Structure::getEntityFromPlace(TypesPackage::Coordinates coordinates) {
                for (int i = 0; i < this->structureEntities.size(); i++) {
                    if (this->structureEntities.at(i).getCoordinates() == coordinates) {
                        return this->structureEntities.at(i);
                    }
                }
                throw std::string("FUCK1234");
            }

            /**
             * \brief Structure height getter
             * \details Standard Structure height getter
             * \return The height of a Structure
             */
            int Structure::getHeight() {
                return this->height;
            }

            /**
             * \brief Structure length getter
             * \details Standard Structure length getter
             * \return The length of a Structure
             */
            int Structure::getLength() {
                return this->length;
            }

            /**
             * \brief Structure tile setter
             * \details Standard Structure tile setter
             * \param tile A tile to paste
             * \param coordinates The coordinates of a tile to paste
             */
            void Structure::setTile(Tile tile, TypesPackage::Coordinates coordinates) {
                this->structureTiles[coordinates.y][coordinates.x] = tile;
            }

            /**
             * \brief Structure entity adder
             * \details Standard Structure entity adder
             * \param entity An entity to add to a Structure
             */
            void Structure::addEntity(EntityPackage::Entity entity) {
                this->structureEntities.push_back(entity);
            }

            /**
            * \brief Structure entity remover
            * \details Standard Structure entity remover
            * \param entityCoordinates The coordinates of an entity to remove
            */
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
