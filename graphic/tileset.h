//
// Created by EgrZver on 23.07.2023.
//
#include <game/locations/tile.h>
#include <map>

#ifndef ROGUENGINE_TILESET_H
#define ROGUENGINE_TILESET_H


namespace RoguEngine {
    namespace GraphicCore {
        /**
         * \brief Tileset class
         * \details The class of a tileset that may stores (as its name says) unlimited number of tiles
         */
        class Tileset {
            private:
                std::map<int, GameCore::LocationsPackage::Tile> tiles;
                int tileCount;
            public:
                void addTile(GameCore::LocationsPackage::Tile tile);
                void removeTile(int id);
                int getTileCount();
                GameCore::LocationsPackage::Tile getTile(int id);
        };

        /**
         * \brief Tile added
         * \details Adds a tile to the tileset
         * \param tile The tile to add
         */
        void Tileset::addTile(GameCore::LocationsPackage::Tile tile) {
            this->tiles[tile.getID()] = tile;
            this->tileCount++;
        }

        /**
         * \brief Tile count getter
         * \details Returns a tile count of the tileset
         * \return The tile count of the tileset
         */
        int Tileset::getTileCount() {
            return this->tileCount;
        }

        /**
         * \brief Tile getter
         * \details Standard tileset tile getter
         * \param id The id of the tile in the tileset
         * \return The tile of the tileset
         */
        GameCore::LocationsPackage::Tile Tileset::getTile(int id) {
            return this->tiles[id];
        }

        /**
         * \brief Tile remover
         * \details Removes a tile from the tileset
         * \param id The id of the tile to remove
         */
        void Tileset::removeTile(int id) {
            this->tiles.erase(this->tiles.find(id));
        }
    }
}


#endif //ROGUENGINE_TILESET_H
