//
// Created by Harutyun Tagushyan on 2020-02-07.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_STATE_H
#define MATCH3GAME_STATE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <stack>

class State;
extern std::stack<State*> states;

class State {
protected:
    sf::RenderWindow* window;
    sf::Event sfEvent;
    std::vector<sf::Texture> textures;
    sf::Vector2i mousePos;

public:
    State(sf::RenderWindow* window);
    virtual ~State();

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void updateSFMLEvents() = 0;
    virtual void updateMousePos();
    sf::Vector2i getMousePos();
};


#endif //MATCH3GAME_STATE_H
