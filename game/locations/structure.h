//
// Created by EgrZver on 25.07.2023.
//
#include <game/locations/tile.h>
#include <game/types/typesPackage.h>
#include <game/entity/entityPackage.h>
#include <game/gamecoreexceptions.h>
#include <fmt/format.h>

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
             * \throw OutOfRangeException when desired place is out of tiles array range
             */
            Tile Structure::getTile(TypesPackage::Coordinates coordinates) {
                if ((coordinates.x >= this->length) || (coordinates.y >= this->height) || (coordinates.x < 0) || (coordinates.y < 0)) {
                    throw CoreExceptions::OutOfRangeException("Out of range when addressing structure tiles array");
                } else {
                    return this->structureTiles[coordinates.y][coordinates.x];
                }
            }

            /**
             * \brief Structure entity getter
             * \details Standard Structure entity getter
             * \param coordinates The coordinates of an entity
             * \return The entity of a Structure on desired coordinates
             * \throw NoEntityFoundException if no entity has been found at desired coordinates
             * \throw OutOfRangeException when desired place is out of tiles array range
             */
            EntityPackage::Entity Structure::getEntityFromPlace(TypesPackage::Coordinates coordinates) {
                if ((coordinates.x >= this->length) || (coordinates.y >= this->height) || (coordinates.x < 0) || (coordinates.y < 0)) {
                    throw CoreExceptions::OutOfRangeException("Out of range in desired entity coordinates");
                } else {
                    for (EntityPackage::Entity& structureEntity : this->structureEntities) {
                        if (structureEntity.getCoordinates() == coordinates) {
                            return structureEntity;
                        }
                    }
                    throw CoreExceptions::NoEntityFoundException(fmt::format("No entity has been found at this place: x: {}, y: {}", coordinates.x, coordinates.y));
                }
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
             * \throw OutOfRangeException when desired place is out of tiles array range
             */
            void Structure::setTile(Tile tile, TypesPackage::Coordinates coordinates) {
                if ((coordinates.x >= this->length) || (coordinates.y >= this->height) || (coordinates.x < 0) || (coordinates.y < 0)) {
                    throw CoreExceptions::OutOfRangeException("Out of range in desired place coordinates");
                } else {
                    this->structureTiles[coordinates.y][coordinates.x] = tile;
                }
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
            * \throw NoEntityFoundException if no entity has been found at desired coordinates
            * \throw OutOfRangeException when entity coordinates are out of location range
            */
            void Structure::removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates) {
                if ((entityCoordinates.x >= this->length) || (entityCoordinates.y >= this->height) || (entityCoordinates.x < 0) || (entityCoordinates.y < 0)) {
                    throw CoreExceptions::OutOfRangeException("Out of range in desired entity coordinates");
                } else {
                    for (auto it = this->structureEntities.begin(); it != this->structureEntities.end(); it++) {
                        if (it->getCoordinates() == entityCoordinates) {
                            this->structureEntities.erase(it);
                            break;
                        }
                    }
                    throw CoreExceptions::NoEntityFoundException(fmt::format("No entity has been found at this place: x: {}, y: {}", entityCoordinates.x, entityCoordinates.y));
                }
            }
        }
    }
}

#endif //ROGUENGINE_STRUCTURE_H
