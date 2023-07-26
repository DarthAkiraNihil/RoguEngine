//
// Created by EgrZver on 26.07.2023.
//
#include <graphic/renderers/locationrenderer.h>

#ifndef ROGUENGINE_GAMEOBJECTRENDERER_H
#define ROGUENGINE_GAMEOBJECTRENDERER_H

namespace RoguEngine {
    namespace GraphicCore {
        namespace RenderersPackage {
            class GameObjectRenderer {
                private:
                    LocationRenderer locationRenderer;
                public:
                    void render(SemiConsolePackage::SemiConsole *console, GameCore::LocationsPackage::Location location, GameCore::TypesPackage::Coordinates where);

            };

            void GameObjectRenderer::render(SemiConsolePackage::SemiConsole *console,
                                            GameCore::LocationsPackage::Location location,
                                            GameCore::TypesPackage::Coordinates where) {
                this->locationRenderer.render(console, location, where);
            }
        }
    }
}

#endif //ROGUENGINE_GAMEOBJECTRENDERER_H
