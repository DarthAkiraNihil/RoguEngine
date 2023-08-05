//
// Created by EgrZver on 05.08.2023.
//
#include <game/types/coordinates.h>
//#include <game/entity/monster.h>
#include <game/locations/location.h>

#ifndef ROGUENGINE_BASEPATHFINDER_H
#define ROGUENGINE_BASEPATHFINDER_H

namespace RoguEngine {
    namespace GameCore {
        namespace PathfindingPackage {
            class BasePathfinder {
                public:
                    virtual TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, LocationsPackage::Location* location) = 0;
            };
        }
    }
}

#endif //ROGUENGINE_BASEPATHFINDER_H
