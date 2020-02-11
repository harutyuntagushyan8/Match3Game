//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Gem.h"

Gem::Gem(sf::RenderWindow* window, int x, int y, int row, int column, sf::Vector2i offset, sf::Texture* tileTexture, int randomGem, sf::Texture* gemTexture) {
    this->window = window;
    this->x = x;
    this->y = y;
    this->row = row;
    this->column = column;
    this->gemNumber = randomGem;
    this->offset = offset;

    spriteBackground = new sf::Sprite;
    spriteForeground = new sf::Sprite;

    spriteBackground->setTexture(*tileTexture);
    spriteBackground->setTextureRect(sf::IntRect(x, y, this->offset.x, this->offset.y));
    spriteBackground->setPosition(this->x, this->y);

    spriteForeground->setTexture(*gemTexture);
    spriteForeground->setPosition(this->x + this->offset.x/2 - gemTexture->getSize().x/2, this->y + this->offset.y/2 - gemTexture->getSize().y/2);
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

void Gem::setGem(sf::Texture* texture) {
    spriteForeground->setTexture(*texture, true);
    spriteForeground->setPosition(this->x + this->offset.x/2 - texture->getSize().x/2, this->y + this->offset.y/2 - texture->getSize().y/2);
}
