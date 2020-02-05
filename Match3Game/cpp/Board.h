//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_BOARD_H
#define MATCH3GAME_BOARD_H

#include <vector>
#include <cstdlib>
#include <cstring>
#include "Gem.h"
#include "ResourcePath.hpp"
#include <exception>
#include <iostream>

class Board {
private:
    int rows;
    int columns;
    std::vector<std::vector<Gem*>> gems;
    std::vector<sf::Texture*> gemTextures;
    std::vector<sf::Sprite*> gemSprites;
    sf::Texture* tile1, *tile2, *h_bomb, *v_bomb;
    sf::Sprite* sprite1, *sprite2, *sprite_h_bomb, *sprite_v_bomb;
    int* holes;
    int holeCount;
    std::vector<std::string> gemIcons = {"blue.png", "green.png", "orange.png", "red.png", "violet.png"};

    void random();
    void createGems();
    void loadResources();

public:
    Board(int w, int h, int holes);
    ~Board();
    int getRows();
    int getColumns();
    void update();
    void render();
    void updateSFMLEvents();

};


#endif //MATCH3GAME_BOARD_H
