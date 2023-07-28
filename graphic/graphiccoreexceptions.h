//
// Created by EgrZver on 27.07.2023.
//
#include <stdexcept>

#ifndef ROGUENGINE_GRAPHICCOREEXCEPTIONS_H
#define ROGUENGINE_GRAPGICCOREEXCEPTIONS_H

namespace RoguEngine {
    namespace GraphicCore {
        namespace CoreExceptions {
            class NoFileFoundException : public std::exception {
                private:
                    std::string message_;
                public:
                    explicit NoFileFoundException(const std::string &message);

                    const char *what() const noexcept override { return message_.c_str(); }
            };

            class InvalidFontImageSizeException : public std::exception {
                private:
                    std::string message_;
                public:
                    explicit InvalidFontImageSizeException(const std::string &message);

                    const char *what() const noexcept override { return message_.c_str(); }
            };

            class InvalidFontLetterIDException : public std::exception {
                private:
                    std::string message_;
                public:
                    explicit InvalidFontLetterIDException(const std::string &message);

                    const char *what() const noexcept override { return message_.c_str(); }
            };

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


#endif //ROGUENGINE_COREEXCEPTIONS_H
