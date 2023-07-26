//
// Created by EgrZver on 24.07.2023.
//

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

            const RGBAData NoColor = {255, 255, 255, 255};
        }
    }
}

#endif //ROGUENGINE_RGBTRINITY_H
