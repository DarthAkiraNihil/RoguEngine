//
// Created by EgrZver on 28.07.2023.
//
#include <stdexcept>

#ifndef ROGUENGINE_GAMECOREEXCEPTIONS_H
#define ROGUENGINE_GAMECOREEXCEPTIONS_H

namespace RoguEngine {
    namespace GameCore {
        namespace CoreExceptions {
            /**
             * \brief NoEntityFound Exception
             * \details This exception is thrown when no entity has benn found in a location.
             * Thrown by these methods:
             * * Location::getEntityFromPlace
             * * Location::removeEntityFromPlace
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
             * Thrown by these methods:
             * * Location::pasteStructure
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
             * Thrown by these methods:
             * * Location::pasteStructure
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
             * Thrown by these methods:
             * * Location::getEntityFromPlace
             * * Location::removeEntityFromPlace
             */
            class OutOfRangeException : public std::exception {
                private:
                    std::string message_;
                public:
                    explicit OutOfRangeException(const std::string &message);

                    const char *what() const noexcept override { return message_.c_str(); }
            };

            NoEntityFoundException::NoEntityFoundException(const std::string &message) : message_(message) {}

            DimensionIncompatibilityException::DimensionIncompatibilityException(const std::string &message) : message_(message) {}

            InvalidStructurePastingPlaceException::InvalidStructurePastingPlaceException(const std::string &message) : message_(message) {}

            OutOfRangeException::OutOfRangeException(const std::string &message) : message_(message) {}
        }
    }
}


#endif //ROGUENGINE_COREEXCEPTIONS_H
