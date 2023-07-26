//
// Created by EgrZver on 26.07.2023.
//
#include <graphic/semiconsole/semiconsole.h>
#include <game/types/typesPackage.h>

#ifndef ROGUENGINE_BASERENDERER_H
#define ROGUENGINE_BASERENDERER_H

namespace RoguEngine {
    namespace GraphicCore {
        namespace RenderersPackage {
            template<class RenderObject>
            class BaseRenderer {
                private:
                    RenderObject assigned;
                public:
                    virtual void render(SemiConsolePackage::SemiConsole window, GameCore::TypesPackage::Coordinates where);
                    void assign(RenderObject renderObject) {
                        this->assigned = renderObject;
                    }
            };
        }
    }
}

#endif //ROGUENGINE_BASERENDERER_H
