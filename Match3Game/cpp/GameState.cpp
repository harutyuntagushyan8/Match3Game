//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "GameState.h"
#include <iostream>

GameState::~GameState() {
    delete player;
}

GameState::GameState(sf::RenderWindow* window) : State(window) {
    player = new Entity(window);
}

void GameState::render() {
    //window->clear();
    player->render();
    window->display();
}

void GameState::update(const float& dt) {
    updateSFMLEvents(dt);
    player->update(dt);
}

void GameState::updateSFMLEvents(const float &dt) {
    while (window->pollEvent(sfEvent)) {
        // Close window: exit
        if (sfEvent.type == sf::Event::Closed) {
            window->close();
        }
        if(sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape) {
            window->close();
        }
    }
}


