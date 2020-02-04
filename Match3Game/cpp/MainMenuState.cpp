//
// Created by Harutyun Tagushyan on 2020-02-04.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "MainMenuState.h"
#include <iostream>

MainMenuState::~MainMenuState() {
    delete button;
}

MainMenuState::MainMenuState(sf::RenderWindow* window) : State(window) {
    icon.loadFromFile(resourcePath() + "icon.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    texture.loadFromFile(resourcePath() + "image.jpg");
    sprite.setTexture(texture);
    font.loadFromFile(resourcePath() + "sansation.ttf");
    button = new Button(window, window->getSize().x/2 - 200.0f, window->getSize().y/2 - 75.0f, 400.0f, 150.0f,
            font, "Start Game", sf::Color(100,200,200,255), sf::Color(100,0,100,255), sf::Color(20,0,50,255));
}

void MainMenuState::render() {
    window->draw(sprite);
    button->render();
}

void MainMenuState::update(const float& dt) {
    updateSFMLEvents(dt);
    updateMousePos();
    button->update(getMousePos());
}

void MainMenuState::updateSFMLEvents(const float &dt) {
    if(button->isPressed()) {

    }
}

