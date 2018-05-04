#include "DebugConsole.h"
#include "Text.h"


DebugConsole::DebugConsole(sf::VideoMode mode, const char *windowName)
:   window(mode, windowName),
    textPosition(0, 0)
{
    
    setCharacterSize(DEFAULT_CHARACTER_SIZE);
    setBackgroundColor(DEFAULT_BACKGROUND_COLOR);
    setTextColor(DEFAULT_TEXT_COLOR);
    currentLine = 0;
}

void DebugConsole::clear() {
    window.clear(backgroundColor);
    currentLine = 0;
}

void DebugConsole::display() {
    window.display();
}

void DebugConsole::print(const char *formatter, ...) {
    va_list args;
    va_start(args, formatter);
    vprint(formatter, args);
    va_end(args);
}

void DebugConsole::vprint(const char *formatter, va_list args) {
    if(currentLine == maxLine) return;
    text.vformat(formatter, args);
    sf::Vector2f offset(0, currentLine*characterSize);
    text.setCharacterSize(characterSize);
    text.setPosition(offset+textPosition);
    #ifdef SFML_STATIC
    text.setFillColor(textColor);
    #else
    text.setColor(textColor);
    #endif
    currentLine++;
    window.draw(text);
}

void DebugConsole::setCharacterSize(float _characterSize) {
    characterSize = _characterSize;
    maxLine = window.getSize().y / characterSize;
    clear();
}

void DebugConsole::setTextPosition(float x, float y) {
    textPosition.x = x;
    textPosition.y = y;
}

void DebugConsole::setTextPosition(sf::Vector2f _textPosition) {
    textPosition = _textPosition;
}

void DebugConsole::setTextColor(sf::Color color) {
    textColor = color;
}

void DebugConsole::setBackgroundColor(sf::Color color) {
    backgroundColor = color;
}
