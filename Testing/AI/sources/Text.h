#ifndef _TEXT_H_
#define _TEXT_H_

#define DEFAULT_CHARACTER_SIZE 20
#define DEFAULT_FONT "resources/Arial.ttf"
#define MAX_BUFFER 255
#include <SFML/Graphics.hpp>
#include <stdarg.h>

class Text: public sf::Text {
    public:
        Text();
        void format(const char *formatter, ...);
        void vformat(const char *formatter, va_list args);
        void setFontName(const char *fontName);
    private:
        sf::Font font;
};

extern Text text;

#endif