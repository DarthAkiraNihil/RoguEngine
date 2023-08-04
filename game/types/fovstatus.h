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
    enum VisitedStatus {
        NotVisited, /// Means that a player hasn't visited a tile so he does not know what is here
        Visited, /// Means that a player has visited a tile
        Unreachable /// Means that a player can't reach a tile
    };

    const bool VISIBLE = true;
    const bool INVISIBLE = false;
}

#endif //ROGUENGINE_FOVSTATUS_H
