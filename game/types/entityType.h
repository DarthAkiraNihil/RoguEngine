//
// Created by EgrZver on 20.07.2023.
//

#ifndef ROGUENGINE_ENTITYTYPE_H
#define ROGUENGINE_ENTITYTYPE_H

namespace RoguEngine {
    namespace GameCore {
        /**
         * /brief Package of Engine types
         * /details Contains all definitions of specific structures, special typedefs of them and required enumerations and constants
         */
        namespace TypesPackage {
            ///Used to represent a type of an entity
            enum EntityType {
                Player, /// Entity type of Player
                Monster
            };
        }
    }
}

#endif //ROGUENGINE_ENTITYTYPE_H
