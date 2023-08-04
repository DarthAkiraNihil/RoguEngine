//
// Created by EgrZver on 21.07.2023.
//
#include <game/locations/tile.h>
#include <game/types/typesPackage.h>
#include <game/locations/structure.h>
#include <game/entity/entity.h>
#include <game/gamecoreexceptions.h>
#include <iostream>
#include <vector>
#include <fmt/format.h>

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
                    int height, length, lightLevel;
                    Tile** locationMap;
                    bool** playerFOV;
                    RoguEnigine::GameCore::TypesPackage::VisitedStatus** visitedMap;
                    EntityPackage::Player* assignedPlayer;
                    std::vector<EntityPackage::Entity> locationEntities;
                    void doFov(float x, float y);
                public:
                    explicit Location(TypesPackage::Pair size);
                    Tile getTile(TypesPackage::Coordinates coordinates);
                    EntityPackage::Entity getEntityFromPlace(TypesPackage::Coordinates coordinates);
                    int getHeight();
                    int getLength();
                    int getLightLevel();
                    int setLightLevel(int newLightLevel);
                    EntityPackage::Player* getAssignedPlayer();
                    void assignPlayer(EntityPackage::Player* assigned);
                    void setTile(Tile tile, TypesPackage::Coordinates coordinates);
                    void addEntity(EntityPackage::Entity entity);
                    void removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates);
                    void pasteStructure(Structure structure, TypesPackage::Coordinates at);
                    bool moveEntity(TypesPackage::Coordinates source, TypesPackage::Coordinates direction);
                    bool movePlayer(TypesPackage::Coordinates direction);
                    bool getFOVStatusAt(TypesPackage::Coordinates where);
                    RoguEnigine::GameCore::TypesPackage::VisitedStatus getVisitedStatusAt(TypesPackage::Coordinates where);
                    void calculateFOV();
            };

            /**
             * \brief Location class constructor
             * \details Standard Location class constructor
             * \param size The size of the location (length x height)
             */
            Location::Location(TypesPackage::Pair size) {
                this->height = size.y;
                this->length = size.x;
                this->lightLevel = 1;
                this->locationMap = new Tile* [height];
                for (int i = 0; i < height; i++) {
                    this->locationMap[i] = new Tile[length];
                }
                this->playerFOV = new bool* [height];
                for (int i = 0; i < height; i++) {
                    this->playerFOV[i] = new bool[length];
                }
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < length; j++) {
                        this->playerFOV[i][j] = false;
                    }
                }

                this->visitedMap = new RoguEnigine::GameCore::TypesPackage::VisitedStatus* [height];
                for (int i = 0; i < height; i++) {
                    this->visitedMap[i] = new RoguEnigine::GameCore::TypesPackage::VisitedStatus[length];
                }
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < length; j++) {
                        this->visitedMap[i][j] = RoguEnigine::GameCore::TypesPackage::VisitedStatus::NotVisited;
                    }
                }

            }

            /**
             * \brief Location tile getter
             * \details Standard Location tile getter
             * \param coordinates The coordinates of a tile
             * \return The tile of a location on desired coordinates
             * \throw OutOfRangeException when desired place is out of tiles array range
             */
            Tile Location::getTile(TypesPackage::Coordinates coordinates) {
                if ((coordinates.x >= this->length) || (coordinates.y >= this->height) || (coordinates.x < 0) || (coordinates.y < 0)) {
                    throw CoreExceptions::OutOfRangeException("Out of range when addressing location tiles array");
                } else {
                    return this->locationMap[coordinates.y][coordinates.x];
                }
            }

            /**
             * \brief Location entity getter
             * \details Standard Location entity getter
             * \param coordinates The coordinates of an entity
             * \return The entity of a location on desired coordinates
             * \throw NoEntityFoundException if no entity has been found at desired coordinates
             * \throw OutOfRangeException when desired place is out of tiles array range
             */
            EntityPackage::Entity Location::getEntityFromPlace(TypesPackage::Coordinates coordinates) {
                if ((coordinates.x >= this->length) || (coordinates.y >= this->height) || (coordinates.x < 0) || (coordinates.y < 0)) {
                    throw CoreExceptions::OutOfRangeException("Out of range in desired entity coordinates");
                } else {
                    for (EntityPackage::Entity& locationEntity : this->locationEntities) {
                        if (locationEntity.getCoordinates() == coordinates) {
                            return locationEntity;
                        }
                    }
                    throw CoreExceptions::NoEntityFoundException(fmt::format("No entity has been found at this place: x: {}, y: {}", coordinates.x, coordinates.y));
                }

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
             * \brief Location light level getter
             * \details Standard Location light level getter
             * \return The light level of a location
             */
            int Location::getLightLevel() {
                return this->lightLevel;
            }

            /**
             * \brief Location light level setter
             * \details Standard Location light level setter
             * \throw InvalidLightLevelException if the passed light level is not positive
             */
            int Location::setLightLevel(int newLightLevel) {
                if (newLightLevel <= 0) {
                    throw CoreExceptions::InvalidLightLevelException("The light level has to be positive");
                } else {
                    this->lightLevel = newLightLevel;
                }
            }

            /**
             * \brief Location tile setter
             * \details Standard Location tile setter
             * \param tile A tile to paste
             * \param coordinates The coordinates of a tile to paste
             * \throw OutOfRangeException when desired place is out of tiles array range
             */
            void Location::setTile(Tile tile, TypesPackage::Coordinates coordinates) {
                if ((coordinates.x >= this->length) || (coordinates.y >= this->height) || (coordinates.x < 0) || (coordinates.y < 0)) {
                    throw CoreExceptions::OutOfRangeException("Out of range in desired place coordinates");
                } else {
                    this->locationMap[coordinates.y][coordinates.x] = tile;
                }
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
             * \throw NoEntityFoundException if no entity has been found at desired coordinates
             * \throw OutOfRangeException when entity coordinates are out of location range
             */
            void Location::removeEntityFromPlace(TypesPackage::Coordinates entityCoordinates) {
                if ((entityCoordinates.x >= this->length) || (entityCoordinates.y >= this->height) || (entityCoordinates.x < 0) || (entityCoordinates.y < 0)) {
                    throw CoreExceptions::OutOfRangeException("Out of range in desired entity coordinates");
                } else {
                    for (auto it = this->locationEntities.begin(); it != this->locationEntities.end(); it++) {
                        if (it->getCoordinates() == entityCoordinates) {
                            this->locationEntities.erase(it);
                            break;
                        }
                    }
                    throw CoreExceptions::NoEntityFoundException(fmt::format("No entity has been found at this place: x: {}, y: {}", entityCoordinates.x, entityCoordinates.y));
                }

            }

            /**
             * \brief Paster of structures
             * \details Pastes a structure into a location
             * \param structure A structure to paste in
             * \param at The coordinates of left top corner of pasting place
             * \throw DimensionIncompatibilityException if the structure does not fit the location
             * \throw InvalidStructurePastingPlaceException if the structure will cause Segmentation fault if it is pasted at desired place
             * \throw OutOfRangeException when desired place is out of tiles array range
             */
            void Location::pasteStructure(Structure structure, TypesPackage::Coordinates at) {
                int structureHeight = structure.getHeight(), structureLength = structure.getLength();
                if ((at.x >= this->length) || (at.y >= this->height) || (at.x < 0) || (at.y < 0)) {
                    throw CoreExceptions::OutOfRangeException("Out of range in desired structure pasting coordinates");
                } else if ((structureHeight > this->height) || (structureLength > this->length)) {
                    throw CoreExceptions::DimensionIncompatibilityException(
                        fmt::format("The structure can't be pasted: it doesn't fit the location size [Structure: h: {}, l: {}; Location: h: {}, l: {}]",structureHeight, structureHeight, this->height, this->length)
                        );
                } else if ((structureHeight  + at.y > this->height) || (structureLength + at.x > this->length)) {
                    throw CoreExceptions::InvalidStructurePastingPlaceException(
                        fmt::format("The structure can't be pasted: it will be out of location range and this may cause segmentation fault (check structure sizes and pasting coordinates)")
                        );
                } else {
                    for (int i = 0; i < structure.getHeight(); i++) {
                        for (int j = 0; j < structure.getLength(); j++) {
                            this->locationMap[at.y + i][at.x + j] = structure.getTile({j, i});
                        }
                    }
                }
            }

            /**
             * \brief Entity mover
             * \details Moves an entity in a location. Before moving it checks if the data is correct (i.e. if the coordinates indicates a valid place).
             * The entity won't be moved if an impassable tile is on its way.
             * \param source The coordinates of the beginning of a place
             * \param direction Moving direction
             * \throw InvalidMovingCoordinatesException if source coordinates are out of location range
             * \throw NoEntityFoundException if no entity has been found at source coordinates
             * \return true if the entity has been moved, else false
             */
            bool Location::moveEntity(TypesPackage::Coordinates source, TypesPackage::Coordinates direction) {
                if ((source.x >= this->length) || (source.y >= this->height) || (source.x < 0) || (source.y < 0)) {
                    throw CoreExceptions::InvalidMovingCoordinatesException("Invalid source coordinates for this location");
                } else if (
                    ((source.x == 0) && (direction.x == -1)) ||
                    ((source.x == this->length - 1) && (direction.x == 1)) ||
                    ((source.y == 0) && (direction.y == -1)) ||
                    ((source.y == this->height - 1) && (direction.y == 1))
                ) {
                    return false;
                }else {
                    for (EntityPackage::Entity& locationEntity : this->locationEntities) {
                        TypesPackage::Coordinates entityCoordinates = locationEntity.getCoordinates();
                        if (entityCoordinates == source) {
                            if (this->getTile({entityCoordinates.x + direction.x, entityCoordinates.y + direction.y}).isPassable()) {
                                locationEntity.move(direction);
                                return true;
                            } else {
                                return false;
                            }
                        }
                    }
                    throw CoreExceptions::NoEntityFoundException(fmt::format("No entity has been found at this place: x: {}, y: {}", source.x, source.y));
                }
            }

            bool Location::getFOVStatusAt(TypesPackage::Coordinates where) {
                if (where.x < 0 || where.y < 0 || where.x >= this->length || where.y >= this->height) {
                    throw CoreExceptions::InvalidFOVPlaceException("Selected place does not exist");
                } else {
                    return this->playerFOV[where.y][where.x];
                }
            }

            RoguEnigine::GameCore::TypesPackage::VisitedStatus Location::getVisitedStatusAt(
                TypesPackage::Coordinates where) {
                if (where.x < 0 || where.y < 0 || where.x >= this->length || where.y >= this->height) {
                    throw CoreExceptions::InvalidFOVPlaceException("Selected place does not exist");
                } else {
                    return this->visitedMap[where.y][where.x];
                }
            }
            void Location::doFov(float x, float y) {
                float ox = (float) this->assignedPlayer->getCoordinates().x+0.5f;
                float oy = (float) this->assignedPlayer->getCoordinates().y+0.5f;
                for(int i = 0; i < this->lightLevel; i++) {
                    if ((int) oy >= 0 && (int) ox >= 0 && (int) oy < this->height && (int) ox < this->length) {
                        this->playerFOV[(int) oy][(int) ox] = true;//Set the tile to visible.
                        if(!this->locationMap[(int) oy][(int) ox].isTrasparent()) return;
                        ox+=x;
                        oy+=y;
                    } else {
                        return;
                    }

                }
            }


            void Location::calculateFOV() {
                for (int i = 0; i < this->height; i++) {
                    for (int j = 0; j < this->length; j++) {
                        this->playerFOV[i][j] = false;
                    }
                }
                for(int i = 0; i < 360; i++) {
                    this->doFov(cos((float)i*0.01745f), sin((float)i*0.01745f));
                }
            }

            EntityPackage::Player* Location::getAssignedPlayer() {
                return this->assignedPlayer;
            }

            void Location::assignPlayer(EntityPackage::Player* assigned) {
                this->assignedPlayer = assigned;
            }

            bool Location::movePlayer(TypesPackage::Coordinates direction) {
                TypesPackage::Coordinates source = this->assignedPlayer->getCoordinates();
                if (
                    ((source.x == 0) && (direction.x == -1)) ||
                    ((source.x == this->length - 1) && (direction.x == 1)) ||
                    ((source.y == 0) && (direction.y == -1)) ||
                    ((source.y == this->height - 1) && (direction.y == 1))
                    ) {
                    return false;
                } else {
                    if (this->getTile({source.x + direction.x, source.y + direction.y}).isPassable()) {
                        this->assignedPlayer->move(direction);
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }
    }
}

#endif //ROGUENGINE_LOCATION_H
