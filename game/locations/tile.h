//
// Created by EgrZver on 21.07.2023.
//
#include <iostream>
#include <game/types/typesPackage.h>
#include <SFML/Graphics.hpp>

#ifndef ROGUENGINE_TILE_H
#define ROGUENGINE_TILE_H

namespace RoguEngine {
    namespace GameCore {
        namespace LocationsPackage {
            /**
             * \brief A class of a graphic tile
             * \details Represents a class of a graphic tile that is used in interface, location etc. rendering.
             * Has the attributes of color, name and pass ability (indicates if an entity can pass through the tile)
             */
            class Tile {
                private:
                    sf::Sprite tileSprite;
                    std::wstring name;
                    TypesPackage::RGBAData color;
                    bool passable;
                public:
                    Tile() = default;
                    Tile(sf::Sprite tileSprite, std::wstring name, bool isPassable, TypesPackage::RGBAData baseColor = TypesPackage::NoColor);
                    std::wstring getName();
                    sf::Sprite getRawSprite();
                    sf::Sprite getRenderedSprite();
                    bool isPassable();
                    void setColor(TypesPackage::RGBAData newColor);
            };



            Tile::Tile(sf::Sprite tileSprite, std::wstring name, bool isPassable, TypesPackage::RGBAData baseColor) {
                this->tileSprite = tileSprite;
                this->name = name;//std::move(name);
                this->passable = isPassable;
                this->color = baseColor;
            }

            std::wstring Tile::getName() {
                return this->name;
            }

            bool Tile::isPassable() {
                return this->passable;
            }

            sf::Sprite Tile::getRawSprite() {
                return this->tileSprite;
            }
            sf::Sprite Tile::getRenderedSprite() {

                if (this->color != TypesPackage::NoColor) {
                    sf::Sprite tmp = this->tileSprite;
                    tmp.setColor(sf::Color(this->color.r, this->color.g, this->color.b, this->color.alpha));
                    return tmp;
                } else {
                    return this->tileSprite;
                }
            }
            void Tile::setColor(TypesPackage::RGBAData newColor) {
                this->color = newColor;
            }

        }
    }
}

#endif //ROGUENGINE_TILE_H
