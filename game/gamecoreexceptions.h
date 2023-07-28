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

            NoEntityFoundException::NoEntityFoundException(const std::string &message) : message_(message) {}

            DimensionIncompatibilityException::DimensionIncompatibilityException(const std::string &message) : message_(message) {}

            InvalidStructurePastingPlaceException::InvalidStructurePastingPlaceException(const std::string &message) : message_(message) {}

            OutOfRangeException::OutOfRangeException(const std::string &message) : message_(message) {}

            InvalidColorException::InvalidColorException(const std::string &message) : message_(message) {}
        }


#endif //ROGUENGINE_GAMECOREEXCEPTIONS_H
