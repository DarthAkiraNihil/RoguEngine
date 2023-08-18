//
// Created by EgrZver on 05.08.2023.
//
#include <iostream>
#include <vector>
#include <game/types/typesPackage.h>
#include <game/entity/entity.h>
//#include <game/pathfinding/basepathfinder.h>
#include <game/gamecoreexceptions.h>
//

#ifndef ROGUENGINE_MONSTER_H
#define ROGUENGINE_MONSTER_H

namespace RoguEngine {
    namespace GameCore {
        namespace EntityPackage {
            class Monster: public Entity {
                private:
                    TypesPackage::MonsterCharacteristics characteristics;
                    std::vector<TypesPackage::Coordinates> currentPath = {};
                    std::vector<TypesPackage::Coordinates> controlPoints = {};
                    int currentControlPointPair;
                    bool hasPathIndicator;
                    int currentPathStep;
                    TypesPackage::Pair radialRPParameters;
                    TypesPackage::MoverType generator;

                    bool isTriggeredNow;

                public:
                    Monster(std::wstring name, sf::Sprite sprite, int maxHP,  TypesPackage::Coordinates coordinates, TypesPackage::MoverType generatorType, int visionRange);
                    int getMaxHP();
                    TypesPackage::Pair getRadialRandomPointParameters();
                    //TypesPackage::Coordinates getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize);
                    TypesPackage::Coordinates getNextMove();
                    bool hasPath();
                    bool isTriggered();
                    void trigger();
                    void untrigger();
                    void assignPath(std::vector<TypesPackage::Coordinates>& pathVector);
                    void addControlPoint(TypesPackage::Coordinates cp);
                    void setRadialRandomPointParameters(TypesPackage::Pair parameters);
                    std::vector<TypesPackage::Coordinates> getNextControlPoints();
                    TypesPackage::MoverType getMoverType();
            };

            Monster::Monster(std::wstring name, sf::Sprite sprite, int maxHP, TypesPackage::Coordinates coordinates, TypesPackage::MoverType generatorType, int visionRange) : Entity(name, TypesPackage::Monster, sprite, coordinates, visionRange) {
                this->characteristics.HP = {maxHP, maxHP};
                this->hasPathIndicator = false;
                this->currentPathStep = 0;
                this->currentControlPointPair = 0;
                this->generator = generatorType;
                this->isTriggeredNow = false;
            }

            int Monster::getMaxHP() {
                return this->characteristics.HP.max;
            }

            //TypesPackage::Coordinates Monster::getNextMove(TypesPackage::Coordinates source, int** passMap, TypesPackage::Pair locationSize) {
            //    return this->mover->getNextMove(source, passMap, locationSize);
            //}

            TypesPackage::MoverType Monster::getMoverType() {
                return this->generator;
            }

            void Monster::assignPath(std::vector<TypesPackage::Coordinates>& pathVector) {
                for (auto & it : pathVector) {
                    this->currentPath.push_back(it);
                }
                this->hasPathIndicator = true;
            }

            bool Monster::hasPath() {
                return this->hasPathIndicator;
            }

            TypesPackage::Coordinates Monster::getNextMove() {
                if (!this->hasPathIndicator) {
                    throw CoreExceptions::NoPathException("The monster has no path, no move to return");
                } else {
                    TypesPackage::Coordinates next = this->currentPath.at(this->currentPath.size() - this->currentPathStep - 1);
                    if (this->currentPathStep == this->currentPath.size() - 1) {
                        this->currentPath.clear();
                        this->hasPathIndicator = false;
                        this->currentPathStep = 0;
                    } else {
                        this->currentPathStep++;
                    }
                    return next;
                }
            }

            void Monster::addControlPoint(TypesPackage::Coordinates cp) {
                this->controlPoints.push_back(cp);
            }

            std::vector<TypesPackage::Coordinates> Monster::getNextControlPoints() {
                if (this->controlPoints.size() < 2) {
                    throw CoreExceptions::NoControlPointsException("The monster has less than 2 control points");
                } else {
                    if (this->currentControlPointPair == this->controlPoints.size() - 1) {
                        std::vector<TypesPackage::Coordinates> pair = {this->controlPoints[this->currentControlPointPair], this->controlPoints[0]};
                        this->currentControlPointPair = 0;
                        return pair;
                    } else {
                        std::vector<TypesPackage::Coordinates> pair = {this->controlPoints[this->currentControlPointPair], this->controlPoints[this->currentControlPointPair + 1]};
                        this->currentControlPointPair++;
                        return pair;
                    }
                }
            }

            void Monster::setRadialRandomPointParameters(TypesPackage::Pair parameters) {
                this->radialRPParameters = parameters;
            }

            TypesPackage::Pair Monster::getRadialRandomPointParameters() {
                return this->radialRPParameters;
            }

            bool Monster::isTriggered() {
                return this->isTriggeredNow;
            }

            void Monster::trigger() {
                this->isTriggeredNow = true;
            }

            void Monster::untrigger() {
                this->isTriggeredNow = false;
            }

        }
    }
}

#endif //ROGUENGINE_MONSTER_H
