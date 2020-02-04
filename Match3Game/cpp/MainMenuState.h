//
// Created by Harutyun Tagushyan on 2020-02-04.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_MAINMENUSTATE_H
#define MATCH3GAME_MAINMENUSTATE_H

#include "State.h"
#include "Button.h"
#include "ResourcePath.hpp"

class MainMenuState : public State {
public:
    MainMenuState(sf::RenderWindow* window);
    ~MainMenuState();

    void update(const float& dt);
    void render();
    void updateSFMLEvents(const float& dt);

private:

    Button* button;
    sf::Font font;
};


#endif //MATCH3GAME_MAINMENUSTATE_H
