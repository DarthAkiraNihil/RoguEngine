//
// Created by EgrZver on 20.07.2023.
//

#ifndef ROGUENGINE_COORDINATES_H
#define ROGUENGINE_COORDINATES_H

namespace RoguEngine::GameCore::TypesPackage {
        /**
        * \brief A structure representing coordinates
        * \details This structure is supposed to represent coordinates of something, but sometimes it's also can be used to represent a pair of numbers.
        * To improve code readability, don't use Coordinates, use its typedef Pair instead
        * Coordinates can be compared as equals (overloaded operator==)
        */
        struct Coordinates {
            int x; /// Represents an abscissa of something, or the first value of the pair
            int y; /// Represents an ordinate of something, or the second value of the pair

        bool operator==(Coordinates const& other) const {
            return this->x == other.x && this->y == other.y;
        }
    };

    const Coordinates DIRECTION_NORTH = {0, -1};
    const Coordinates DIRECTION_SOUTH = {0, 1};
    const Coordinates DIRECTION_WEST = {-1, 0};
    const Coordinates DIRECTION_EAST = {1, 0};

    const Coordinates DIRECTION_NORTH_WEST = {1 , -1};
    const Coordinates DIRECTION_NORTH_EAST = {-1 , -1};
    const Coordinates DIRECTION_SOUTH_WEST = {1 , 1};
    const Coordinates DIRECTION_SOUTH_EAST = {-1 , 1};

    typedef Coordinates Pair; /// A typedef to improve code readability. Use when you need to store just a pair of ints that is not coordinates.
}
#endif //ROGUENGINE_COORDINATES_H
