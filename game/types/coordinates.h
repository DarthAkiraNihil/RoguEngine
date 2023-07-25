//
// Created by EgrZver on 20.07.2023.
//

#ifndef ROGUENGINE_COORDINATES_H
#define ROGUENGINE_COORDINATES_H

namespace RoguEngine {
    namespace GameCore {
        namespace TypesPackage {
            struct Coordinates {
                int x, y;

                bool operator==(Coordinates const& other) const {
                    return this->x == other.x && this->y == other.y;
                }
            };

            const Coordinates DIRECTION_NORTH = {0, 1};
            const Coordinates DIRECTION_SOUTH = {0, -1};
            const Coordinates DIRECTION_WEST = {1, 0};
            const Coordinates DIRECTION_EAST = {-1, 0};

            const Coordinates DIRECTION_NORTH_WEST = {-1 , 1};
            const Coordinates DIRECTION_NORTH_EAST = {1 , 1};
            const Coordinates DIRECTION_SOUTH_WEST = {-1 , -1};
            const Coordinates DIRECTION_SOUTH_EAST = {1 , -1};

            typedef Coordinates Pair;
        }
    }
}
#endif //ROGUENGINE_COORDINATES_H
