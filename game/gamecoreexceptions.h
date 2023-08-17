//
// Created by EgrZver on 28.07.2023.
//
#include <stdexcept>

#ifndef ROGUENGINE_GAMECOREEXCEPTIONS_H
#define ROGUENGINE_GAMECOREEXCEPTIONS_H

namespace RoguEngine::GameCore::CoreExceptions {
    /**
     * \brief NoEntityFound Exception
     * \details This exception is thrown when no entity has benn found in a location.
     */
    class NoEntityFoundException : public std::exception {
        private:
            std::string message_;
        public:
            explicit NoEntityFoundException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief DimensionIncompatibility Exception
     * \details This exception is thrown when a structure can't be pasted into a location because the structure can't fit the location size
     */
    class DimensionIncompatibilityException : public std::exception {
        private:
            std::string message_;
        public:
            explicit DimensionIncompatibilityException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief InvalidStructurePastingPlace Exception
     * \details This exception is thrown when a structure can't be pasted at a place of a location because the structure won't fit the location (may cause Segmentation Fault)
     */
    class InvalidStructurePastingPlaceException : public std::exception {
        private:
            std::string message_;
        public:
            explicit InvalidStructurePastingPlaceException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief OutOfRange Exception
     * \details This exception is thrown when something is out of something's range like array, sequence etc. All information is in the exception message
     */
    class OutOfRangeException : public std::exception {
        private:
            std::string message_;
        public:
            explicit OutOfRangeException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief InvalidColor Exception
     * \details This exception is thrown when you try to convert RGBAData to sf::Color using convertToSFML but RGBA parameters are out of allowed range
     */
    class InvalidColorException : public std::exception {
        private:
            std::string message_;
        public:
            explicit InvalidColorException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief InvalidMovingCoordinates Exception
     * \details This exception is thrown when... maybe it's not used for a while?
     */
    class InvalidMovingCoordinatesException : public std::exception {
        private:
            std::string message_;
        public:
            explicit InvalidMovingCoordinatesException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief InvalidFOVPlace Exception
     * \details This exception is thrown when you try to get FOV status of a tile that is out of locaiton range
     */
    class InvalidFOVPlaceException : public std::exception {
        private:
            std::string message_;
        public:
            explicit InvalidFOVPlaceException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief InvalidLightLevel Exception
     * \details This exception is thrown when you try to declare location light level as something below zero
     */
    class InvalidLightLevelException : public std::exception {
        private:
            std::string message_;
        public:
            explicit InvalidLightLevelException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief NoPath Exception
     * \details This exception is thrown when a monster has no its own path and this tries to get the next move
     */
    class NoPathException : public std::exception {
        private:
            std::string message_;
        public:
            explicit NoPathException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief NoControlPoints Exception
     * \details This exception is thrown when you try to get next control points of a monster but if has less than 2 of them
     */
    class NoControlPointsException : public std::exception {
        private:
            std::string message_;
        public:
            explicit NoControlPointsException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * \brief NoAssignedLocation Exception
     * \details This exception is thrown when a pathfinder has no assigned location to find path in
     */
    class NoAssignedLocationException : public std::exception {
        private:
            std::string message_;
        public:
            explicit NoAssignedLocationException(const std::string &message);

            const char *what() const noexcept override { return message_.c_str(); }
    };

    NoAssignedLocationException::NoAssignedLocationException(const std::string &message) : message_(message) {}

    NoControlPointsException::NoControlPointsException(const std::string &message) : message_(message) {}


    NoEntityFoundException::NoEntityFoundException(const std::string &message) : message_(message) {}

    DimensionIncompatibilityException::DimensionIncompatibilityException(const std::string &message) : message_(
        message) {}

    InvalidStructurePastingPlaceException::InvalidStructurePastingPlaceException(const std::string &message) : message_(
        message) {}

    OutOfRangeException::OutOfRangeException(const std::string &message) : message_(message) {}

    InvalidColorException::InvalidColorException(const std::string &message) : message_(message) {}

    InvalidMovingCoordinatesException::InvalidMovingCoordinatesException(const std::string &message) : message_(message) {}

    InvalidFOVPlaceException::InvalidFOVPlaceException(const std::string &message) : message_(message) {}

    InvalidLightLevelException::InvalidLightLevelException(const std::string &message) : message_(message) {}

    NoPathException::NoPathException(const std::string &message) : message_(message) {}
}


#endif //ROGUENGINE_GAMECOREEXCEPTIONS_H
