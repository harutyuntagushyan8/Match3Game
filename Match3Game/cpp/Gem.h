//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_GEM_H
#define MATCH3GAME_GEM_H

#include "SFML/Graphics.hpp"
#include "ResourcePath.hpp"

class Gem {
private:
    int x;
    int y;
    sf::Texture textureBackground;
    sf::Texture textureForeground;
    sf::Sprite spriteBackground;
    sf::Sprite spriteForeground;
    sf::RenderWindow* window;

public:
    Gem(sf::RenderWindow*, int, int, sf::Vector2i, sf::Texture&, sf::Texture&);
    void update();
    void render();
    void updateSFMLEvents();

};


#endif //MATCH3GAME_GEM_H
