//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Gem.h"

Gem::Gem(sf::RenderWindow* window, int x, int y, sf::Vector2i offset, sf::Texture* tileTexture, sf::Texture* gemTexture) {
    this->window = window;
    spriteBackground = new sf::Sprite;
    spriteForeground = new sf::Sprite;

    spriteBackground->setTexture(*tileTexture);
    spriteBackground->setTextureRect(sf::IntRect(x, y, offset.x, offset.y));
    spriteBackground->setPosition(x, y);

    spriteForeground->setTexture(*gemTexture);
    spriteForeground->setTextureRect(sf::IntRect(x + offset.x/5, y + offset.y/5, 3 * offset.x/5, 3 * offset.y/5));
    spriteForeground->setPosition(x + offset.x/5, y + offset.y/5);
}

Gem::~Gem() {
    delete spriteBackground;
    delete spriteForeground;
}

void Gem::render() {
    window->draw(*spriteBackground);
    window->draw(*spriteForeground);
}

void Gem::updateSFMLEvents() {

}

void Gem::update() {

}
