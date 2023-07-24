//
// Created by EgrZver on 23.07.2023.
//
#include <game/locations/tile.h>
#include <map>

#ifndef ROGUENGINE_TILESET_H
#define ROGUENGINE_TILESET_H


namespace RoguEngine {
    namespace GraphicCore {
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

        void Tileset::addTile(GameCore::LocationsPackage::Tile tile) {
            this->tiles[tile.getID()] = tile;
            this->tileCount++;
        }

        int Tileset::getTileCount() {
            return this->tileCount;
        }

        GameCore::LocationsPackage::Tile Tileset::getTile(int id) {
            return this->tiles[id];
        }

        void Tileset::removeTile(int id) {
            this->tiles.erase(this->tiles.find(id));
        }
    }
}


#endif //ROGUENGINE_TILESET_H
