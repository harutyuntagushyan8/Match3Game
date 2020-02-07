//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_GAMESTATE_H
#define MATCH3GAME_GAMESTATE_H

#include "State.h"
#include "Board.h"
#include <stack>

class GameState : public State {
protected:
    void initWindow();
    void updateSFMLEvents();
    void update();
    void render();

    // Variables
    Board* board;
    const int ROWS = 6;
    const int COLUMNS = 6;
    const int HOLESCOUNT = 3;
    const int X = 300;
    const int Y = 300;
    const sf::Vector2i OFFSET{150, 150};

public:
    GameState(sf::RenderWindow* window);
    ~GameState();
};

#endif //MATCH3GAME_GAMESTATE_H
