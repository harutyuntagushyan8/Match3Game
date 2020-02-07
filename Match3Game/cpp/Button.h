//
// Created by Harutyun Tagushyan on 2020-02-07.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_BUTTON_H
#define MATCH3GAME_BUTTON_H

#include "State.h"
#include "GameState.h"

enum button_states {
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button {
public:
    Button(sf::RenderWindow* window, float x, float y, float width, float height, sf::Font font, std::string text,
            sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();

    void update(sf::Vector2i mousePos);
    void render();
    void updateSFMLEvents();
    const bool isPressed();

private:
    Button() = default;
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Font font;
    sf::RectangleShape shape;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    unsigned short buttonState;
};


#endif //MATCH3GAME_BUTTON_H
