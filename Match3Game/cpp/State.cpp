//
// Created by Harutyun Tagushyan on 2020-02-07.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "State.h"

State::State(sf::RenderWindow* window) {
    this->window = window;
}

void State::updateMousePos() {
    mousePos = sf::Mouse::getPosition(*window);
}

sf::Vector2i State::getMousePos() {
    return mousePos;
}

State::~State() {

}
