//
// Created by EgrZver on 05.08.2023.
//

#ifndef ROGUENGINE_MOVERTYPE_H
#define ROGUENGINE_MOVERTYPE_H

namespace RoguEngine {
    namespace GameCore {
        namespace TypesPackage {
            enum MoverType {
                RandomDumb,
                RandomRational,
                Patrol,
                RandomPointEverywhere,
                RandomPointRadial,
                //RandomLineDirection
            };
        }
    }
}

#endif //ROGUENGINE_MOVERTYPE_H
