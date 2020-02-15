//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_GEM_H
#define MATCH3GAME_GEM_H

#include "SFML/Graphics.hpp"
#include "ResourcePath.hpp"

enum class GemType { Blue, Green, Orange, Red, Violet, SolidColor};

class Gem {
private:
    sf::Sprite* spriteBackground;
    sf::Sprite* spriteForeground;
    sf::RenderWindow* window;

public:
    Gem(sf::RenderWindow*, int, int, int, int, sf::Vector2i, GemType, sf::Texture*, int, sf::Texture*);
    int x;
    int y;
    int row;
    int column;
    sf::Vector2i offset;
    int gemNumber;
    void setGemTexture(sf::Texture*);
    void setGemType(GemType);
    GemType type;
    int matchCount = 0;
    ~Gem();
    void update();
    void render();
    void updateSFMLEvents();

};


#endif //MATCH3GAME_GEM_H
