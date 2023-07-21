//
// Created by EgrZver on 21.07.2023.
//
#include <iostream>
#include "game/auxiliary/auxiliaryPackage.h"

#ifndef ROGUENGINE_TILE_H
#define ROGUENGINE_TILE_H

namespace RoguEngine {
    namespace GameCore {
        namespace LocationsPackage {
            class Tile {
                private:
                    wchar_t symbol;
                    std::wstring name;
                    //AuxiliaryPackage::Coordinates coordinates;
                    bool passedBy;
                public:
                    Tile() = default;
                    Tile(wchar_t symbol, std::wstring name, /*AuxiliaryPackage::Coordinates coordinates,*/ bool isPassable);
                    wchar_t getChar();
                    std::wstring getName();
                    //AuxiliaryPackage::Coordinates getCoordinates();
                    bool isPassable();
            };



            Tile::Tile(wchar_t symbol, std::wstring name,/* AuxiliaryPackage::Coordinates coordinates,*/ bool isPassable) {
                this->symbol = symbol;
                this->name = name;
                //this->coordinates = coordinates;
                this->passedBy = isPassable;
            }

            wchar_t Tile::getChar() {
                return this->symbol;
            }

            std::wstring Tile::getName() {
                return this->name;
            }

            //AuxiliaryPackage::Coordinates Tile::getCoordinates() {
            //    return this->coordinates;
            //}

            bool Tile::isPassable() {
                return this->passedBy;
            }
        }
    }
}

#endif //ROGUENGINE_TILE_H
