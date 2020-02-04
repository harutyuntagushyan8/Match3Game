//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Game.h"
#include "ResourcePath.hpp"
#include "MainMenuState.h"
#include <iostream>

// Initializer functions
void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Match3 Game");
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(false);
}

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

// Functions
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

void Game::update() {
    updateSFMLEvents();

    if(!states.empty()) {
        states.top()->update(dt);
    } else {
        window->close();
    }
}

void Game::render() {
    window->clear();

    if(!states.empty()) {
        states.top()->render();
    }

    window->display();
}

void Game::run() {
    while (window->isOpen()) {
        //updateDt();
        updateSFMLEvents();
        update();
        render();
    }
}

//void Game::updateDt() {
//    dt = dtClock.restart().asSeconds();
//    std::cout << "FPS = " << 1.f/dt << "\n";
//}

void Game::initStates() {
    states.push(new MainMenuState(window));
}


