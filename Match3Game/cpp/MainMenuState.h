//
// Created by Harutyun Tagushyan on 2020-02-07.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_MAINMENUSTATE_H
#define MATCH3GAME_MAINMENUSTATE_H

#include "State.h"
#include "Button.h"
#include "ResourcePath.hpp"

class MainMenuState : public State {
private:
    void initWindow();

    // Variables
    Button* startButton;
    sf::Event sfEvent;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite welcomeScreen;

public:
    MainMenuState(sf::RenderWindow* window);
    void updateSFMLEvents();
    void update();
    void render();
};


#endif //MATCH3GAME_MAINMENUSTATE_H
