//
// Created by EgrZver on 27.07.2023.
//
#include <stdexcept>

#ifndef ROGUENGINE_GRAPHICCOREEXCEPTIONS_H
#define ROGUENGINE_GRAPHICCOREEXCEPTIONS_H

namespace RoguEngine {
    namespace GraphicCore {
        namespace CoreExceptions {
            /**
             * \brief NoFileFound Exception
             * \details This exception is thrown when it's not possible to load a file because it does not exist
             */
            class NoFileFoundException : public std::exception {
                private:
                    std::string message_;
                public:
                    explicit NoFileFoundException(const std::string &message);

                    const char *what() const noexcept override { return message_.c_str(); }
            };

            /**
             * \brief InvalidFontImageSize Exception
             * \details This exception is thrown when you try to load a font image file but its size is invalid that may cause addressing non-existent image pixels or loading the font with corrupted symbols
             */
            class InvalidFontImageSizeException : public std::exception {
                private:
                    std::string message_;
                public:
                    explicit InvalidFontImageSizeException(const std::string &message);

                    const char *what() const noexcept override { return message_.c_str(); }
            };

            /**
             * \brief InvalidFontLetterID Exception
             * \details This exception is thrown when ypu try to draw a symbol with ID less than 0 or greater than 255
             */
            class InvalidFontLetterIDException : public std::exception {
                private:
                    std::string message_;
                public:
                    explicit InvalidFontLetterIDException(const std::string &message);

                    const char *what() const noexcept override { return message_.c_str(); }
            };

            /**
             * \brief InvalidDrawingCoordinates Exception
             * \details This exception is thrown when drawing coordinates are out of range or drawing cannot be applied because a game object won't fit the SemiConsole
             */
            class InvalidDrawingCoordinatesException : public std::exception {
                private:
                    std::string message_;
                public:
                    explicit InvalidDrawingCoordinatesException(const std::string &message);

                    const char *what() const noexcept override { return message_.c_str(); }
            };

            InvalidFontImageSizeException::InvalidFontImageSizeException(const std::string &message) : message_(message) {}

            NoFileFoundException::NoFileFoundException(const std::string &message) : message_(message) {}

            InvalidFontLetterIDException::InvalidFontLetterIDException(const std::string &message) : message_(message) {}

            InvalidDrawingCoordinatesException::InvalidDrawingCoordinatesException(const std::string &message) : message_(message) {}
        }
    }
}


#endif //ROGUENGINE_GRAPHICCOREEXCEPTIONS_H
