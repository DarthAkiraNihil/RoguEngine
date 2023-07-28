//
// Created by EgrZver on 24.07.2023.
//
//#include <graphic/tileset.h>
#include <game/types/typesPackage.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fmt/format.h>
#include <graphic/graphiccoreexceptions.h>
//#include <map>

#ifndef ROGUENGINE_SCFONT_H
#define ROGUENGINE_SCFONT_H

namespace RoguEngine::GraphicCore::SemiConsolePackage {
            /**
             * \brief Class of a font of SemiConsole.
             * \details This class is used to represent a font for SemiConsole. Able to only 256 symbols which are defined in CP437 and nowhere else.
             * But still, it does not matter what you want to use as a font. It may be everything that fits the size (the size of one symbol x the size of loadable image of a font).
             */
            class SemiConsoleFont {
                private:
                    sf::Texture fontFace[256];
                    GameCore::TypesPackage::Pair size{};
                public:
                    SemiConsoleFont(std::string fontFileName, GameCore::TypesPackage::Pair size);
                    sf::Sprite getBaseLetter(int id);
            };

            /**
             * \brief SemiConsoleFont Constructor
             * \details Standard SemiConsoleFont class constructor
             * \param fontFileName The file name of the font. Must be an image
             * \param size The dimensions of a symbol tile (length * height)
             * \throw NoFileFoundException if no source image file has been found
             * \throw InvalidFontImageSizeException if source image has invalid size
             */
            SemiConsoleFont::SemiConsoleFont(std::string fontFileName, GameCore::TypesPackage::Pair size) {
                this->size = size;
                sf::Image sizeChecker;
                if (!sizeChecker.loadFromFile(fontFileName)) {
                    throw CoreExceptions::NoFileFoundException(fmt::format("No file found with the name \"{}\"", fontFileName));
                } else {
                    sf::Vector2u fontImageSize = sizeChecker.getSize();
                    if ((fontImageSize.x != size.x * 16) || (fontImageSize.y != size.y * 16)) {
                        throw CoreExceptions::InvalidFontImageSizeException(
                            fmt::format("According to the font size, font image source file size should be {}x{} but got {}x{}",
                                        size.x * 16,
                                        size.y * 16,
                                        fontImageSize.x,
                                        fontImageSize.y
                                        ));
                    } else {
                        for (int i = 0; i < 16; i++) {
                            for (int j = 0; j < 16; j++) {
                                sf::Texture loaded;
                                if (loaded.loadFromFile(fontFileName, sf::IntRect(j*16, i*16, size.x, size.y))) {
                                    this->fontFace[i*16 + j] = loaded;//sf::Sprite(loaded);
                                }
                            }
                        }
                    }
                }
            }

            /**
             * \brief Base letter getter
             * \details Returns a symbol of the font face without transformation, transforming it into a Sprite
             * \param id The id of a font symbol
             * \return The Symbol sprite without any transformation
             * \throw InvalidFontLetterIDException if invalid ID has been passed
             */
            sf::Sprite SemiConsoleFont::getBaseLetter(int id) {
                if ((id > 255) || (id < 0)) {
                    throw CoreExceptions::InvalidFontLetterIDException(fmt::format("No letter with the following ID: {}", id));
                } else {
                    return sf::Sprite(this->fontFace[id]);
                }
            }
        }

#endif //ROGUENGINE_SCFONT_H
