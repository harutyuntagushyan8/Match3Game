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

    Game();

    // Variables
    sf::RenderWindow* window;
    sf::Event sfEvent;

    float dt;
    sf::Clock dtClock;

public:
    virtual ~Game();
    void run();
    static Game& getInstance() {
        static Game instance;
        return instance;
    }
    std::stack<State*> states;

};


#endif //MATCH3GAME_GAME_H
