//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Gem.h"

Gem::Gem(sf::RenderWindow* window, int x, int y, sf::Vector2i offset, sf::Texture& textureBackground, sf::Texture& textureForeground) {
    this->window = window;
    this->textureBackground = textureBackground;
    this->textureForeground = textureForeground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setTextureRect(sf::IntRect(x, y, offset.x, offset.y));
    spriteBackground.setPosition(x, y);
    spriteForeground.setTexture(textureForeground);
    spriteForeground.setTextureRect(sf::IntRect(x, y, offset.x, offset.y));
    spriteForeground.setPosition(x, y);
}

void Gem::update() {

}

void Gem::render() {
    window->draw(spriteBackground);
    window->draw(spriteForeground);
}

void Gem::updateSFMLEvents() {

}
