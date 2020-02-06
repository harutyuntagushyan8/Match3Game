//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Gem.h"

Gem::Gem(int x, int y, sf::Texture* textureBackground, sf::Texture* textureForeground) {
    this->textureBackground = textureBackground;
    this->textureForeground = textureForeground;
    spriteBackground->setTexture(*textureBackground);
    spriteForeground->setTexture(*textureForeground);
}

void Gem::update() {

}

void Gem::render() {
    window->draw(*spriteBackground);
    window->draw(*spriteForeground);
}

void Gem::updateSFMLEvents() {

}
