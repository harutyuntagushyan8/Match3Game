//
// Created by Harutyun Tagushyan on 2020-02-07.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_GAME_H
#define MATCH3GAME_GAME_H

#include "GameState.h"
#include "MainMenuState.h"
#include "Button.h"

class Game {
private:
    void initWindow();
    void initStates();
    void updateSFMLEvents();
    void update();
    void render();

    // Variables
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Image icon;
    sf::Music music;

     const int WINDOW_WIDTH = 1500;
     const int WINDOW_HEIGHT = 1500;
     const std::string TITLE = "Match3 Game";

public:
    Game();
    ~Game();
    void run();
};

#endif //MATCH3GAME_GAME_H
