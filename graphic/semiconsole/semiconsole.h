//
// Created by EgrZver on 23.07.2023.

//


#include <graphic/semiconsole/scfont.h>
#include <game/types/typesPackage.h>
#include <game/locations/locationsPackage.h>
#include <game/gamecoreexceptions.h>
//#include <graphic/renderers/gameobjectrenderer.h>
#include <iostream>

#ifndef ROGUENGINE_SEMICONSOLE_H
#define ROGUENGINE_SEMICONSOLE_H

namespace RoguEngine {
    namespace GraphicCore {
        namespace SemiConsolePackage {
            /**
             *
             */
            class SemiConsole {
                private:
                    SemiConsoleFont font;
                    GameCore::TypesPackage::Pair tileSize, windowTileSize;


                public:
                    sf::RenderWindow window; ///The RenderWindow of the SemiConsole. It's public because it's hard enough to make the full interface for it
                    SemiConsole(std::string fontFileName, GameCore::TypesPackage::Pair fontSize,
                                GameCore::TypesPackage::Pair windowTileSize);
                    void putChar(int id, GameCore::TypesPackage::Coordinates at);
                    void putColoredChar(int id, GameCore::TypesPackage::Coordinates at,
                                        GameCore::TypesPackage::RGBAData color);
                    sf::Sprite getChar(int id) {
                        return this->font.getBaseLetter(id);
                    } //todo remove
                    void renderGameObject(GameCore::LocationsPackage::Location location,
                                          GameCore::TypesPackage::Coordinates where);

            };

            /**
             * \brief SemiConsole class constructor
             * \details Standard SemiConsole class constructor
             * \param fontFileName The File name of the font
             * \param fontSize This size of the font
             * \param windowTileSize The dimensions of window in tiles (font tile size x window tile size)
             * \throw NoFileFoundException if no source image file of the font has been found
             */
            SemiConsole::SemiConsole(std::string fontFileName, GameCore::TypesPackage::Pair fontSize,
                                     GameCore::TypesPackage::Pair windowTileSize) : window(
                sf::VideoMode(fontSize.x * windowTileSize.x, fontSize.y * windowTileSize.y), "Fkcing test"),
                                                                                    font(fontFileName, fontSize) {
                this->tileSize = fontSize;
                this->windowTileSize = windowTileSize;
            }

            /**
             * \brief Function to draw a symbol of the font
             * \details Draws a desired symbol of the console font at desired place
             * \param id The id of the symbol to draw
             * \param at The coordinates of the place where to draw
             * \throw InvalidFontLetterIDException if invalid ID of the char has been passed
             * \throw InvalidDrawingCoordinatesException if drawing coordinates are out of drawing range (SemiConsole drawing window)
             */
            void SemiConsole::putChar(int id, GameCore::TypesPackage::Coordinates at) { //todo int -> enum
                sf::Sprite puttingChar = this->font.getBaseLetter(id);
                if ((at.x >= this->windowTileSize.x) || (at.y >= this->windowTileSize.y) || (at.x < 0) || (at.y < 0)) {
                    throw CoreExceptions::InvalidDrawingCoordinatesException("Drawing coordinates out of drawing range");
                } else {
                    puttingChar.setPosition(at.x * this->tileSize.x, at.y * this->tileSize.y);
                    this->window.draw(puttingChar);
                }
            }

            /**
             * \brief Function to draw a symbol of the font with a color
             * \details Draws a desired symbol of the console font at desired place with a desired color
             * \param id The id of the symbol to draw
             * \param at The coordinates of the place where to draw
             * \param color The color of the symbol to draw
             * \throw InvalidFontLetterIDException if invalid ID of the char has been passed
             * \throw InvalidDrawingCoordinatesException if drawing coordinates are out of drawing range (SemiConsole drawing window)
             * \throw InvalidColorException if invalid color has been passed
             */
            void SemiConsole::putColoredChar(int id, GameCore::TypesPackage::Coordinates at,
                                             GameCore::TypesPackage::RGBAData color) {
                sf::Sprite puttingChar = this->font.getBaseLetter(id);
                if ((at.x >= this->windowTileSize.x) || (at.y >= this->windowTileSize.y) || (at.x < 0) || (at.y < 0)) {
                    throw CoreExceptions::InvalidDrawingCoordinatesException("Drawing coordinates out of drawing range");
                } else {
                    puttingChar.setPosition(at.x * this->tileSize.x, at.y * this->tileSize.y);
                    puttingChar.setColor(GameCore::TypesPackage::convertToSFML(color));
                    this->window.draw(puttingChar);
                }
            }

            /**
             * \brief Renderer of a game location
             * \param location The location to render
             * \param where The coordinates of the left top corner of the location to render
             */
            void SemiConsole::renderGameObject(GameCore::LocationsPackage::Location location,
                                               GameCore::TypesPackage::Coordinates where) {
                if ((where.x >= this->windowTileSize.x) || (where.y >= this->windowTileSize.y) || (where.x < 0) || (where.y < 0)) {
                    throw CoreExceptions::InvalidDrawingCoordinatesException("Drawing coordinates out of drawing range");
                } else if ((where.x + location.getLength() > this->windowTileSize.x) || (where.y + location.getHeight() > this->windowTileSize.y)) {
                    throw CoreExceptions::InvalidDrawingCoordinatesException("Game object will not fit the SemiConsole at this place");
                } else {
                    for (int i = 0; i < location.getHeight(); i++) {
                        for (int j = 0; j < location.getLength(); j++) {
                            if (location.getFOVStatusAt({j, i})) {
                                sf::Sprite tmp = location.getTile({j, i}).getRenderedSprite();
                                tmp.setPosition((where.x + j) * 16, (where.y + i) * 16);
                                this->window.draw(tmp);
                            } else if (location.getVisitedStatusAt({j, i})){
                                sf::Sprite tmp = location.getTile({j, i}).getRenderedSprite();
                                tmp.setPosition((where.x + j) * 16, (where.y + i) * 16);
                                tmp.setColor(sf::Color(40, 40, 40, 255));
                                this->window.draw(tmp);
                            }



                        }
                    }
                    sf::Sprite player = location.getAssignedPlayer()->getSprite();
                    GameCore::TypesPackage::Coordinates playerCoordinates = location.getAssignedPlayer()->getCoordinates();
                    player.setPosition((where.x + playerCoordinates.x) * 16, (where.y + playerCoordinates.y) * 16);
                    this->window.draw(player);
                    for (auto it = location.locationMonstersBegin(); it != location.locationMonstersEnd(); it++) {
                        GameCore::TypesPackage::Coordinates monsterCoordinates = it->getCoordinates();
                        if (location.getFOVStatusAt((*it).getCoordinates())) {
                            sf::Sprite tmp = (*it).getSprite();
                            tmp.setPosition((where.x + monsterCoordinates.x) * 16, (where.y + monsterCoordinates.y) * 16);
                            this->window.draw(tmp);
                        }
                    }
                }

            }
        }
    }
}


#endif //ROGUENGINE_SEMICONSOLE_H
