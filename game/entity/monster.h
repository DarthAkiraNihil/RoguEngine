//
// Created by EgrZver on 05.08.2023.
//
#include <iostream>
#include <game/entity/entity.h>

#ifndef ROGUENGINE_MONSTER_H
#define ROGUENGINE_MONSTER_H

namespace RoguEngine {
    namespace GameCore {
        namespace EntityPackage {
            class Monster: public Entity {
                private:
                    std::wstring name;
                    TypesPackage::EntityType entityType;
                    sf::Sprite sprite;
                    TypesPackage::Coordinates coordinates;
                public:
            };
        }
    }
}

#endif //ROGUENGINE_MONSTER_H
