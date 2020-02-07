//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "GameState.h"
#include "ResourcePath.hpp"

GameState::GameState(sf::RenderWindow* window) : State(window) {
    initWindow();
}

GameState::~GameState() {
    delete board;
}

void GameState::initWindow() {
    board = new Board(window, X, Y, ROWS, COLUMNS, OFFSET, HOLESCOUNT);
}

void GameState::updateSFMLEvents() {
    // Process events
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

void GameState::update() {
    updateSFMLEvents();

    board->update();
}

void GameState::render() {
    window->clear(sf::Color(82, 96, 102, 255));
    board->render();
}



