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
            /**
             * \brief Location class
             * \details A class that represents a game location. Contains only one layer of tiles.
             * Also stores information about all entities in the location. A structure can be pasted in here.
             */
            class Location {
                private:
                    int height, length;
                    Tile** locationMap;
                    std::vector<EntityPackage::Entity> locationEntities;
                public:
                    explicit Location(TypesPackage::Pair size);
                    Tile getTile(TypesPackage::Coordinates coordinates);
                    EntityPackage::Entity getEntityFromPlace(TypesPackage::Coordinates coordinates);
                    int getHeight();
                    int getLength();
                    void setTile(Tile tile, TypesPackage::Coordinates coordinates);
                    void addEntity(EntityPackage::Entity entity);
                    void removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates);
                    void pasteStructure(Structure structure, TypesPackage::Coordinates at);
            };

            /**
             * \brief Location class constructor
             * \details Standard Location class constructor
             * \param size The size of the location (length x height)
             */
            Location::Location(TypesPackage::Pair size) {
                this->height = size.y;
                this->length = size.x;
                this->locationMap = new Tile* [height];
                for (int i = 0; i < length; i++) {
                    this->locationMap[i] = new Tile[length];
                }
            }

            /**
             * \brief Location tile getter
             * \details Standard Location tile getter
             * \param coordinates The coordinates of a tile
             * \return The tile of a location on desired coordinates
             */
            Tile Location::getTile(TypesPackage::Coordinates coordinates) {
                return this->locationMap[coordinates.y][coordinates.x];
            }

            /**
             * \brief Location entity getter
             * \details Standard Location entity getter
             * \param coordinates The coordinates of an entity
             * \return The entity of a location on desired coordinates
             */
            EntityPackage::Entity Location::getEntityFromPlace(TypesPackage::Coordinates coordinates) {
                for (int i = 0; i < this->locationEntities.size(); i++) {
                    if (this->locationEntities.at(i).getCoordinates() == coordinates) {
                        return this->locationEntities.at(i);
                    }
                }
                throw std::string("FUCK1234");
            }

            /**
             * \brief Location height getter
             * \details Standard Location height getter
             * \return The height of a location
             */
            int Location::getHeight() {
                return this->height;
            }

            /**
             * \brief Location length getter
             * \details Standard Location length getter
             * \return The length of a location
             */
            int Location::getLength() {
                return this->length;
            }

            /**
             * \brief Location tile setter
             * \details Standard Location tile setter
             * \param tile A tile to paste
             * \param coordinates The coordinates of a tile to paste
             */
            void Location::setTile(Tile tile, TypesPackage::Coordinates coordinates) {
                this->locationMap[coordinates.y][coordinates.x] = tile;
            }

            /**
             * \brief Location entity adder
             * \details Standard Location entity adder
             * \param entity An entity to add to a location
             */
            void Location::addEntity(EntityPackage::Entity entity) {
                this->locationEntities.push_back(entity);
            }

            /**
             * \brief Location entity remover
             * \details Standard Location entity remover
             * \param entityCoordinates The coordinates of an entity to remove
             */
            void Location::removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates) {
                for (auto it = this->locationEntities.begin(); it != this->locationEntities.end(); it++) {
                    if (it->getCoordinates() == entityCoordinates) {
                        this->locationEntities.erase(it);
                        break;
                    }
                }
            }

            /**
             * \brief Paster of structures
             * \details Pastes a structure into a location
             * \param structure A structure to paste in
             * \param at The coordinates of left top corner of pasting place
             */
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
