//
// Created by EgrZver on 24.07.2023.
//
#include <SFML/Graphics.hpp>
#include <game/gamecoreexceptions.h>
#include <fmt/format.h>

#ifndef ROGUENGINE_RGBTRINITY_H
#define ROGUENGINE_RGBTRINITY_H

namespace RoguEngine {
    namespace GameCore {
        namespace TypesPackage {
            /**
             * \brief RGBA color representation
             * \details A structure that stores values of an RGBA color including r, g, b and alpha components.
             * Can be compared to equality or inequality (overloaded operator== and operator!=)
             */
            struct RGBAData {
                int r, g, b, alpha;

                bool operator==(RGBAData const& other) const {
                    return this->r == other.r && this->g == other.g && this->b == other.b && this->alpha == other.alpha;
                }

                bool operator!=(RGBAData const& other) const {
                    return this->r != other.r || this->g != other.g || this->b != other.b || this->alpha != other.alpha;
                }
            };

            sf::Color convertToSFML(RGBAData color) {
                if (
                    (color.r > 255) ||
                    (color.g > 255) ||
                    (color.b > 255) ||
                    (color.alpha > 255) ||
                    (color.r < 0) ||
                    (color.g < 0) ||
                    (color.b < 0) ||
                    (color.alpha < 0)
                    ) {
                    throw CoreExceptions::InvalidColorException(
                        fmt::format("The color with the following parameters does not exist: r: {}, g: {}, b: {}, alpha: {}",
                        color.r,
                        color.g,
                        color.b,
                        color.alpha));
                } else {
                    return sf::Color(color.r, color.g, color.b, color.alpha);
                }
            }
            const RGBAData NoColor = {255, 255, 255, 255};
        }
    }
}

#endif //ROGUENGINE_RGBTRINITY_H
