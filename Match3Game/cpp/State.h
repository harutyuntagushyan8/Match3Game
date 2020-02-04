//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_STATE_H
#define MATCH3GAME_STATE_H

#include "Entity.h"

class State {
protected:
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Image icon;
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::Texture> textures;
    sf::Vector2i mousePos;

public:
    State(sf::RenderWindow* window);
    virtual ~State();

    virtual void update(const float& dt) = 0;
    virtual void render() = 0;
    virtual void updateSFMLEvents(const float& dt) = 0;
    virtual void updateMousePos();
    sf::Vector2i getMousePos();
};


#endif //MATCH3GAME_STATE_H
