//
// Created by EgrZver on 05.08.2023.
//

#ifndef ROGUENGINE_LIMITEDPAIR_H
#define ROGUENGINE_LIMITEDPAIR_H

namespace RoguEngine {
    namespace GameCore {
        namespace TypesPackage {
            struct LimitedPair {
                int current, max;

                LimitedPair operator+(int arg) {
                    if (this->current + arg <= this->max) {
                        return LimitedPair{this->current + arg, this->max};
                    } else {
                        return LimitedPair{this->max, this->max};
                    }
                }

                LimitedPair operator-(int arg) {
                    if (this->current - arg >= 0) {
                        return LimitedPair{this->current - arg, this->max};
                    } else {
                        return LimitedPair{0, this->max};
                    }
                }
            };
        }
    }
}

#endif //ROGUENGINE_LIMITEDPAIR_H
