//
// Created by Harutyun Tagushyan on 2020-02-07.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "MainMenuState.h"

MainMenuState::~MainMenuState() {
    delete startButton;
}

MainMenuState::MainMenuState(sf::RenderWindow* window) : State(window) {
    initWindow();
}

void MainMenuState::initWindow() {
    font.loadFromFile(resourcePath() + "Sansation_Italic.ttf");
    backgroundTexture.loadFromFile(resourcePath() + "welcome.png");
    welcomeScreen.setTexture(backgroundTexture);
    float scaleX  = (float)window->getSize().x / backgroundTexture.getSize().x;
    float scaleY  = (float)window->getSize().y / backgroundTexture.getSize().y;
    welcomeScreen.setScale(scaleX, scaleY);
    startButton = new Button(window, window->getSize().x/2 - 350, window->getSize().y/2 - 150, 700, 300, font,
            "Start Game", sf::Color(100,200,200,255), sf::Color(100,0,100,255), sf::Color(50,0,50,255));
}

void MainMenuState::render() {
    window->draw(welcomeScreen);
    startButton->render();
}

void MainMenuState::update() {
    updateSFMLEvents();
    updateMousePos();
    startButton->update(getMousePos());
}

void MainMenuState::updateSFMLEvents() {
    if(startButton->isPressed()) {

    }
}

