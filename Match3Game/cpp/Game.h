//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_GAME_H
#define MATCH3GAME_GAME_H

#include "GameState.h"

class Game {
private:
    void initWindow();
    void initStates();
    void updateDt();
    void updateSFMLEvents();
    void update();
    void render();

    // Variables
    sf::RenderWindow* window;
    sf::Event sfEvent;

    float dt;
    sf::Clock dtClock;
    std::stack<State*> states;

public:
    Game();
    virtual ~Game();
    void run();

};


#endif //MATCH3GAME_GAME_H
