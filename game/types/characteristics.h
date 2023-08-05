//
// Created by EgrZver on 05.08.2023.
//
#include "limitedpair.h"

#ifndef ROGUENGINE_CHARACTERISTICS_H
#define ROGUENGINE_CHARACTERISTICS_H

namespace RoguEngine {
    namespace GameCore {
        namespace TypesPackage {
            struct PlayerCharacteristics {
                LimitedPair HP;
            };

            struct MonsterCharacteristics {
                LimitedPair HP;
            };
        }
    }
}

#endif //ROGUENGINE_CHARACTERISTICS_H
