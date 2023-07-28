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
             * The class is immutable by sprite, name and pass ability
             */
            class Tile {
                private:
                    int id;
                    sf::Sprite tileSprite;
                    std::wstring name;
                    TypesPackage::RGBAData color;
                    bool passable;
                public:
                    Tile() = default;
                    Tile(int id, sf::Sprite tileSprite, std::wstring name, bool isPassable, TypesPackage::RGBAData baseColor);
                    int getID();
                    std::wstring getName();
                    sf::Sprite getRawSprite();
                    sf::Sprite getRenderedSprite();
                    bool isPassable();
                    void setColor(TypesPackage::RGBAData newColor);
            };


            /**
             * \brief The default class constructor
             * \details The default Tile constructor
             * \param tileSprite The sptire of a tile
             * \param name The name of a tile. Used in game logging
             * \param isPassable Indicator if an entity can pass through a tile
             * \param baseColor The color of a tile
             */
            Tile::Tile(int id, sf::Sprite tileSprite, std::wstring name, bool isPassable, TypesPackage::RGBAData baseColor) {
                this->id = id;
                this->tileSprite = tileSprite;
                this->name = name;//std::move(name);
                this->passable = isPassable;
                this->color = baseColor;
            }

            int Tile::getID() {
                return this->id;
            }
            /**
             * \brief Name getter
             * \details Standard Tile's name getter
             * \return The name of a tile
             */
            std::wstring Tile::getName() {
                return this->name;
            }

            /**
             * \brief Pass ability indicator getter
             * \details Standard Tile's pass ability getter
             * \return The pass ability indicator of a tile
             */
            bool Tile::isPassable() {
                return this->passable;
            }

            /**
             * \brief Raw sprite getter
             * \details Standard Tile's raw sprite getter. It is used when you want to render a tile "as is" i.e. ignoring its color attribute.
             * \return The raw sprite of a tile
             */
            sf::Sprite Tile::getRawSprite() {
                return this->tileSprite;
            }

            /**
             * \brief Rendered sprite getter
             * \details Standard Tile's rendered sprite getter. It is used when you want to render a tile with specified color (defined by baseColor attribute)
             * If the color is not defined (baseColor = TypesPackage::NoColor) then the sprite will be returned "as is"
             * \return The rendered sprite of a tile or raw version of it (ignoring color)
             */
            sf::Sprite Tile::getRenderedSprite() {

                if (this->color != TypesPackage::NoColor) {
                    sf::Sprite tmp = this->tileSprite;
                    tmp.setColor(sf::Color(this->color.r, this->color.g, this->color.b, this->color.alpha));
                    return tmp;
                } else {
                    return this->tileSprite;
                }
            }

            /**
             * \brief Color setter
             * \details Standard Tile's color setter
             */
            void Tile::setColor(TypesPackage::RGBAData newColor) {
                this->color = newColor;
            }

        }
    }
}

#endif //ROGUENGINE_TILE_H
