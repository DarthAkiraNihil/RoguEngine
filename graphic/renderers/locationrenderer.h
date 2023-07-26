//
// Created by EgrZver on 26.07.2023.
//
#include <graphic/definitions.h>
#include <game/locations/locationsPackage.h>
#include <game/types/typesPackage.h>

#ifndef ROGUENGINE_LOCATIONRENDERER_H
#define ROGUENGINE_LOCATIONRENDERER_H

namespace RoguEngine {
    namespace GraphicCore {
        namespace RenderersPackage {
            class LocationRenderer {
                public:
                    void render(SemiConsolePackage::SemiConsole *console, GameCore::LocationsPackage::Location location, GameCore::TypesPackage::Coordinates where);
            };

            void LocationRenderer::render(SemiConsolePackage::SemiConsole *console,
                                          GameCore::LocationsPackage::Location location,
                                          GameCore::TypesPackage::Coordinates where) {

                for (int i = 0; i < location.getHeight(); i++) {
                    for (int j = 0; j < location.getLength(); j++) {
                        sf::Sprite tmp = location.getTile({j, i}).getRawSprite();
                        tmp.setPosition((where.x + j) * 16, (where.y + i) * 16);
                        //console->;
                    }
                }
            }
        }
    }
}

#endif //ROGUENGINE_LOCATIONRENDERER_H
