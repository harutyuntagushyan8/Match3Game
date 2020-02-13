//
// Created by Harutyun Tagushyan on 2020-02-07.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Game.h"
#include "ResourcePath.hpp"

std::stack<State*> states;

// Constructors/Destructors
Game::Game() {
    initWindow();
    initStates();
}

Game::~Game() {
    delete window;
    while (!states.empty()) {
        delete states.top();
        states.pop();
    }
}

void Game::initStates() {
    states.push(new MainMenuState(window));
}

// Initializer functions
void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(false);

    icon.loadFromFile(resourcePath() + "icon.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    music.openFromFile(resourcePath() + "music.ogg");
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

// Update all in entities
void Game::update() {
    updateSFMLEvents();

    if(!states.empty()) {
        states.top()->update();
    }
}

// Render into window
void Game::render() {
    window->clear();

    if(!states.empty()) {
        states.top()->render();
    }

    window->display();
}

// Run game loop
void Game::run() {
    //music.play();
    while (window->isOpen()) {
        updateSFMLEvents();
        update();
        render();
    }
}
