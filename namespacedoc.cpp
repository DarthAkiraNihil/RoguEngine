//
// Created by EgrZver on 27.07.2023.
//

/**
 * \brief The Library namespace
 * \details The main namespace of the Library RoguEngine. Contains some Core namespaces
 */
namespace RoguEngine {
    /**
     * \brief Game Core namespace
     * \details The namespace of Game Core of the library. Contains packages (as namespaces) that are used to release a game's mechanic.
     * Sometimes its packages are used in other cores
     */
    namespace GameCore {
        /**
         * \brief Namespace of Game core exceptions
         * \details Contains definitions all exceptions used in this core. Sometimes its exceptions are used in other cores (by throwing the exceptions)
         */
        namespace CoreExceptions {

        }

        /**
         * \brief Package of Entities
         * \details Contains definitions of all classes that are inherited from base entity class (including it).
         * Package file - entityPackage.h
         */
        namespace EntityPackage {

        }
        /**
         * \brief Package of Locations
         * \details Contains definitions of all classes that are used to represent different types of locations (dungeons, structures etc.)
         * Package file - locationsPackage.h
         */
        namespace LocationsPackage {

        }
        /**
         * \brief Package of Types
         * \details Contains definitions of all auxiliary types used in this library
         * Package file - typesPackage.h
         */
        namespace TypesPackage {

        }
    }

    /**
     * \brief Graphic Core namespace
     * \details The namespace of Graphic Core of the library. Contains packages (as namespaces) that are used to release a game's GUI
     */
    namespace GraphicCore {
        /**
         * \brief Namespace of Graphic core exceptions
         * \details Contains definitions all exceptions used in this core
         */
        namespace CoreExceptions {

        }

        /**
         * \brief Package of SemiConsole
         * \details Contains definitions SemiConsole and SemiConsoleFont classes that are used to draw a game window
         * Package file - no
         */
        namespace SemiConsolePackage {

        }
    }
}