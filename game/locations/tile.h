//
// Created by EgrZver on 21.07.2023.
//
#include <iostream>
#include "game/types/typesPackage.h"

#ifndef ROGUENGINE_TILE_H
#define ROGUENGINE_TILE_H

namespace RoguEngine {
    namespace GameCore {
        namespace LocationsPackage {
            class Tile {
                private:
                    wchar_t symbol;
                    std::wstring name;
                    bool passedBy;
                public:
                    Tile() = default;
                    Tile(wchar_t symbol, std::wstring name, bool isPassable);
                    wchar_t getChar();
                    std::wstring getName();
                    bool isPassable();
            };



            Tile::Tile(wchar_t symbol, std::wstring name, bool isPassable) {
                this->symbol = symbol;
                this->name = name;
                this->passedBy = isPassable;
            }

            wchar_t Tile::getChar() {
                return this->symbol;
            }

            std::wstring Tile::getName() {
                return this->name;
            }

            bool Tile::isPassable() {
                return this->passedBy;
            }

            //const Tile voidTile = Tile(32, L"void", false);
        }
    }
}

#endif //ROGUENGINE_TILE_H
