//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Game.h"
#include "ResourcePath.hpp"

// Constructors/Destructors
Game::Game() {
    initWindow();
}

Game::~Game() {
    delete window;
    delete board;
}

// Initialize window
void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Match3 Game");
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(false);

    icon.loadFromFile(resourcePath() + "icon.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    music.openFromFile(resourcePath() + "nice_music.ogg");

    // Initialize board
    board = new Board(window, X, Y, ROWS, COLUMNS,OFFSET, HOLESCOUNT);

}

// Update events
void Game::updateSFMLEvents() {
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

// Update all in game
void Game::update() {
    updateSFMLEvents();

    board->update();
}

// Render window
void Game::render() {
    window->clear(sf::Color(100, 120, 130, 255));
    board->render();
    window->display();
}

void Game::run() {
    music.play();
    while (window->isOpen()) {
        update();
        render();
    }
}


