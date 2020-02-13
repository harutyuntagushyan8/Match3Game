//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include <iostream>
#include "GameState.h"
#include "ResourcePath.hpp"

GameState::GameState(sf::RenderWindow* window) : State(window) {
    initWindow();
}

void GameState::initWindow() {
    tile1 = new sf::Texture;
    tile2 = new sf::Texture;
    h_bomb = new sf::Texture;
    v_bomb = new sf::Texture;
    bomb = new sf::Texture;
    gemTextures.resize(gemIcons.size());
    for(int i = 0; i < gemTextures.size(); ++i) {
        gemTextures[i] = new sf::Texture;
    }
    loadResources();

    mainShape.setPosition(0, 0);
    mainShape.setSize(sf::Vector2f(window->getSize().x, 150));
    mainShape.setFillColor(sf::Color(170, 170, 170, 255));
    shapeForMoveCount.setPosition(510, 0);
    shapeForMoveCount.setSize(sf::Vector2f(200, 150));
    shapeForMoveCount.setFillColor(sf::Color(80, 80, 80, 255));
    float x = 10.0f;
    for(int i = 0; i < gemIcons.size(); ++i) {
        menuGems.push_back(sf::Sprite(*gemTextures[i]));
        menuGems[i].setPosition(x, 20);
        x += 100.0f;
    }

    board = new Board(window, X, Y, ROWS, COLUMNS, OFFSET, HOLESCOUNT);
}

void GameState::loadResources() {
    tile1->loadFromFile(resourcePath() + "tile_1.png");
    tile2->loadFromFile(resourcePath() + "tile_2.png");
    h_bomb->loadFromFile(resourcePath() + "h_bomb.png");
    v_bomb->loadFromFile(resourcePath() + "v_bomb.png");
    bomb->loadFromFile(resourcePath() + "bomb.png");
    for(int i = 0; i < gemTextures.size(); ++i) {
        gemTextures[i]->loadFromFile(resourcePath() + gemIcons[i]);
    }
}

void GameState::updateSFMLEvents() {
    // Process events
    while (window->waitEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) {
            window->close();
        }
        if(sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::Escape) {
            window->close();
        }
        if (sfEvent.type == sf::Event::MouseButtonPressed && sfEvent.mouseButton.button == sf::Mouse::Left) {
            mousePos = sf::Mouse::getPosition(*window);
            if(mousePos.x <= X + OFFSET.x * COLUMNS && mousePos.x >= X &&
                mousePos.y <= Y + OFFSET.y * ROWS && mousePos.y >= X) {
                clickedPos = mousePos;
                board->updateMouseClickedPos(clickedPos);
                continue;
            }
        }
        if (sfEvent.type == sf::Event::MouseButtonReleased) {
            mousePos = sf::Mouse::getPosition(*window);
            if(mousePos.x <= X + OFFSET.x * COLUMNS && mousePos.x >= X &&
                mousePos.y <= Y + OFFSET.y * ROWS && mousePos.y >= Y) {
                releasedPos = mousePos;
                board->updateMouseReleasedPos(releasedPos);
                break;
            }
        }
    }
}

void GameState::update() {
    updateSFMLEvents();
    board->update();
}

void GameState::render() {
    window->clear(sf::Color(82, 96, 102, 255));
    window->draw(mainShape);
    window->draw(shapeForMoveCount);
    for(int i = 0; i < menuGems.size(); ++i) {
        window->draw(menuGems[i]);
    }
    board->render();
}


