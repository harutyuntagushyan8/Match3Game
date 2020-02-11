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
    x = 10.0f;
    for(int i = 0; i < gemCounts.size(); ++i) {
        gemTexts.push_back(sf::Text());
        gemTexts[i].setFont(font);
        gemTexts[i].setFillColor(sf::Color::White);
        gemTexts[i].setString(gemCounts[i]);
        gemTexts[i].setCharacterSize(60);
        gemTexts[i].setPosition(x + 10, 80);
        x += 100.0f;
    }
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString(std::to_string(moveCount));
    text.setCharacterSize(100);
    text.setPosition(510 + 200/2 - text.getLocalBounds().width/2, 10);

    board = new Board(window, X, Y, ROWS, COLUMNS, OFFSET, HOLESCOUNT);
}

void GameState::loadResources() {
    font.loadFromFile(resourcePath() + "Sansation_Italic.ttf");
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
            if(mousePos.x <= 1200 && mousePos.x >= 300 &&
                mousePos.y <= 1200 && mousePos.y >= 300) {
                clickedPos = mousePos;
                board->updateMouseClickedPos(clickedPos);
                std::cout << "Click ";
                std::cout << "x = " << mousePos.x << " y = " << mousePos.y << "\n";
                continue;
            }
        }
        if (sfEvent.type == sf::Event::MouseButtonReleased) {
            mousePos = sf::Mouse::getPosition(*window);
            if(mousePos.x <= 1200 && mousePos.x >= 300 &&
                mousePos.y <= 1200 && mousePos.y >= 300) {
                releasedPos = mousePos;
                board->updateMouseReleasedPos(releasedPos);
                std::cout << "Release ";
                std::cout << "x = " << mousePos.x << " y = " << mousePos.y << "\n";
                break;
            }
        }
    }
}

void GameState::update() {
    updateSFMLEvents();
    //updateMousePos();
    //board->update();
}

void GameState::render() {
    window->clear(sf::Color(82, 96, 102, 255));
    window->draw(mainShape);
    window->draw(shapeForMoveCount);
    window->draw(text);
    for(int i = 0; i < menuGems.size(); ++i) {
        window->draw(menuGems[i]);
    }
    for(int i = 0; i < gemTexts.size(); ++i) {
        window->draw(gemTexts[i]);
    }
    board->render();
}


