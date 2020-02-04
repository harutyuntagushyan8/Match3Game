//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_GAMESTATE_H
#define MATCH3GAME_GAMESTATE_H

#include "State.h"
#include "Button.h"

class GameState : public State {
public:
    GameState(sf::RenderWindow* window);
    ~GameState();

    void update(const float& dt);
    void render();
    void updateSFMLEvents(const float& dt);

private:
    Entity* player;
    Button* button;
};


#endif //MATCH3GAME_GAMESTATE_H
