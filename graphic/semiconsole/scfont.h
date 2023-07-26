//
// Created by EgrZver on 24.07.2023.
//
//#include <graphic/tileset.h>
#include <game/types/typesPackage.h>
#include <iostream>
#include <SFML/Graphics.hpp>
//#include <map>

#ifndef ROGUENGINE_SCFONT_H
#define ROGUENGINE_SCFONT_H

namespace RoguEngine::GraphicCore::SemiConsolePackage {
            class SemiConsoleFont {
                private:
                    sf::Texture fontFace[256];
                    //std::map<int, sf::Sprite> fontFace;
                    GameCore::TypesPackage::Pair size;
                public:
                    SemiConsoleFont(std::string fontFileName, GameCore::TypesPackage::Pair size);
                    sf::Sprite getBaseLetter(int id);

            };

            SemiConsoleFont::SemiConsoleFont(std::string fontFileName, GameCore::TypesPackage::Pair size) {
                this->size = size;
                for (int i = 0; i < 16; i++) {
                    for (int j = 0; j < 16; j++) {
                        sf::Texture loaded;
                        if (loaded.loadFromFile(fontFileName, sf::IntRect(j*16, i*16, size.x, size.y))) {
                            this->fontFace[i*16 + j] = loaded;//sf::Sprite(loaded);
                        }
                    }
                }
            }

            sf::Sprite SemiConsoleFont::getBaseLetter(int id) {
                return sf::Sprite(this->fontFace[id]);
            }
        }

#endif //ROGUENGINE_SCFONT_H
