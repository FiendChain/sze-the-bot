#ifndef _DEBUG_CONSOLE_
#define _DEBUG_CONSOLE_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdarg.h>

#define DEFAULT_BACKGROUND_COLOR sf::Color::Black
#define DEFAULT_TEXT_COLOR       sf::Color::White

class DebugConsole {
    public:
        DebugConsole(sf::VideoMode mode, const char *windowName);
        void clear();
        void display();
        void print(const char *formatter, ...);
        void vprint(const char *formatter, va_list args);
        void setCharacterSize(float _characterSize);
        void setTextPosition(float x, float y);
        void setTextPosition(sf::Vector2f _textPosition);
        void setTextColor(sf::Color color);
        void setBackgroundColor(sf::Color color);
    private:
        // internalize the window (composition)
        sf::RenderWindow window;
        // text properties
        sf::Color textColor;
        sf::Color backgroundColor;
        sf::Vector2f textPosition;
        void showText();
        // lines
        float characterSize;
        int currentLine;
        int maxLine;

};

#endif