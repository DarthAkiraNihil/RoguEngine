//
// Created by EgrZver on 23.07.2023.
//
#include <graphic/semiconsole/scfont.h>
#include <game/types/typesPackage.h>
#include <iostream>

#ifndef ROGUENGINE_SEMICONSOLE_H
#define ROGUENGINE_SEMICONSOLE_H

namespace RoguEngine {
    namespace GraphicCore {
        namespace SemiConsolePackage {
            class SemiConsole {
                private:
                    SemiConsoleFont font;
                    GameCore::TypesPackage::Pair tileSize, windowTileSize;

                public:
                    sf::RenderWindow window; // todo make private and add interface
                    SemiConsole(std::string fontFileName, GameCore::TypesPackage::Pair fontSize, GameCore::TypesPackage::Pair windowTileSize);
                    void putChar(int id, GameCore::TypesPackage::Coordinates at);
                    void putColoredChar(int id, GameCore::TypesPackage::Coordinates at, GameCore::TypesPackage::RGBAData color);
            };

            SemiConsole::SemiConsole(std::string fontFileName, GameCore::TypesPackage::Pair fontSize,
                                     GameCore::TypesPackage::Pair windowTileSize) : window(sf::VideoMode(fontSize.x * windowTileSize.x, fontSize.y * windowTileSize.y), "Fkcing test"),
                                                                                    font(fontFileName, fontSize){
                this->tileSize = fontSize;
                this->windowTileSize = windowTileSize;
            }

            void SemiConsole::putChar(int id, GameCore::TypesPackage::Coordinates at) {
                sf::Sprite puttingChar = this->font.getBaseLetter(id);
                puttingChar.setPosition(at.x * this->tileSize.x, at.y * this->tileSize.y);
                this->window.draw(puttingChar);
            }

            void SemiConsole::putColoredChar(int id, GameCore::TypesPackage::Coordinates at,
                                             GameCore::TypesPackage::RGBAData color) {
                sf::Sprite puttingChar = this->font.getBaseLetter(id);
                puttingChar.setPosition(at.x * this->tileSize.x, at.y * this->tileSize.y);
                puttingChar.setColor(sf::Color(color.r, color.g, color.b, color.alpha));
                this->window.draw(puttingChar);
            }
        }
    }
}


#endif //ROGUENGINE_SEMICONSOLE_H
