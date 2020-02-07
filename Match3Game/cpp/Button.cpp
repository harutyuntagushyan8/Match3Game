//
// Created by Harutyun Tagushyan on 2020-02-07.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Button.h"

Button::~Button() {

}

Button::Button(sf::RenderWindow* window, float x, float y, float width, float height, sf::Font font, std::string text,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) {
    this->window = window;
    buttonState = BTN_IDLE;
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::Black);
    this->text.setString(text);
    this->text.setCharacterSize(120);
    this->text.setPosition(
            window->getSize().x / 2.0f -  shape.getSize().x / 2.0f,
            window->getSize().y / 2.0f -  shape.getSize().y / 2.0f + this->text.getLocalBounds().height / 2.0f
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
    shape.setFillColor(this->idleColor);
}

void Button::render() {
    window->draw(shape);
    window->draw(text);
}

void Button::update(sf::Vector2i mousePos) {
    buttonState = BTN_IDLE;
    if(shape.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
        buttonState = BTN_HOVER;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            buttonState = BTN_ACTIVE;
            states.push(new GameState(window));
        }
    }
    switch (buttonState) {
        case BTN_IDLE : shape.setFillColor(idleColor);
            break;
        case BTN_HOVER : shape.setFillColor(hoverColor);
            break;
        case BTN_ACTIVE : shape.setFillColor(activeColor);
            break;
        default: shape.setFillColor(sf::Color::Red);
            break;
    }
}

void Button::updateSFMLEvents() {

}

const bool Button::isPressed() {
    if(buttonState == BTN_ACTIVE)
        return true;
    return false;
}
