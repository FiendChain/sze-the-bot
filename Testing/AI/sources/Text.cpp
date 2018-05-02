#include "Text.h"
#include <stdarg.h>

Text::Text() {
    setFontName(DEFAULT_FONT);
    setCharacterSize(DEFAULT_CHARACTER_SIZE);
    setPosition(0, 0);
    #ifdef SFML_STATIC
    setFillColor(sf::Color::White);
    #else
    setColor(sf::Color::White);
    #endif
}

void Text::format(const char *formatter, ...) {
    va_list args;
    va_start(args, formatter);
    vformat(formatter, args);
    va_end(args); 
}

void Text::vformat(const char *formatter, va_list args) {
    char buffer[MAX_BUFFER] = {0};
    vsnprintf(buffer, MAX_BUFFER, formatter, args);
    setString(buffer); 
}

void Text::setFontName(const char *fontName) {
    font.loadFromFile(fontName);
    setFont(font);
}