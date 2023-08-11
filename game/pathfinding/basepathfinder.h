//
// Created by EgrZver on 05.08.2023.
//
#include <game/types/coordinates.h>
#include <game/types/movertype.h>
//#include <game/entity/monster.h>
//#include <game/locations/location.h>

#ifndef ROGUENGINE_BASEPATHFINDER_H
#define ROGUENGINE_BASEPATHFINDER_H

namespace RoguEngine {
    namespace GameCore {
        namespace PathfindingPackage {
            class BasePathfinder {
                public:
                    virtual TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) = 0;
                    virtual TypesPackage::MoverType getMoverType() = 0;
            };
        }
    }
}

#endif //ROGUENGINE_BASEPATHFINDER_H
