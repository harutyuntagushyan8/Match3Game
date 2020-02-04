//
// Created by Harutyun Tagushyan on 2020-02-03.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_ENTITY_H
#define MATCH3GAME_ENTITY_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <vector>
#include <stack>
#include <map>

class Entity {
public:
    Entity(sf::RenderWindow*);
    virtual ~Entity();

    virtual void update(const float& dt);
    virtual void render();
    virtual void updateSFMLEvents(const float& dt);
    virtual void move(const float& dt, const float x, const float y);

protected:
    sf::RectangleShape shape;
    float movementSpeed;
    sf::RenderWindow* window;
    sf::Event sfEvent;
};


#endif //MATCH3GAME_ENTITY_H
