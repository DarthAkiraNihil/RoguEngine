//
// Created by EgrZver on 03.08.2023.
//

#ifndef ROGUENGINE_FOVSTATUS_H
#define ROGUENGINE_FOVSTATUS_H

namespace RoguEnigine::GameCore::TypesPackage {
    /**
    * \brief FOV status indicators
    * \details This enumeration is for FOV status indication, as its name speaks so. FOV exists only for a player
    */
    enum FOVStatus {
        NotVisited, /// Means that a player hasn't visited a tile so he does not know what is here
        VisitedUnseen, /// Means that a player has visited a tile but he does not see it
        VisitedSeen /// Means that a player has visited a tile and he sees it
    };
}

#endif //ROGUENGINE_FOVSTATUS_H
