//
// Created by Harutyun Tagushyan on 2020-02-03.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Entity.h"

Entity::Entity(sf::RenderWindow* window) : window(window) {
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::White);
    movementSpeed = 100.f;
}

Entity::~Entity() {

}

void Entity::move(const float &dt, const float x, const float y) {
    shape.move(x * movementSpeed * dt, y * movementSpeed * dt);
}

void Entity::update(const float &dt) {
    updateSFMLEvents(dt);
}

void Entity::render() {
    window->draw(shape);
}

void Entity::updateSFMLEvents(const float& dt) {
    while(window->pollEvent(sfEvent)) {
        if(sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::A)
            move(dt, -1.0f, 0.0f);
        if(sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::W)
            move(dt, 1.0f, 0.0f);
        if(sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::D)
            move(dt, 0.0f, -1.0f);
        if(sfEvent.type == sf::Event::KeyPressed && sfEvent.key.code == sf::Keyboard::S)
            move(dt, 0.0f, 1.0f);
    }
}
