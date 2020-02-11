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
#include <stack>

class State;
extern std::stack<State*> states;

class Board {
private:
    int originX;
    int originY;
    int rows;
    int columns;
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Vector2i offset;
    std::vector<std::vector<Gem*>> gems;
    std::vector<int> holes;
    int holeCount;
    sf::Vector2i releasedPos;
    sf::Vector2i clickedPos;
    std::vector<sf::Sprite> menuGems;
    std::vector<sf::Texture*> gemTextures;
    sf::Texture* tile1, *tile2, *h_bomb, *v_bomb, *bomb;
    std::vector<std::string> gemIcons = {"blue.png", "green.png", "orange.png", "red.png", "violet.png"};
    std::vector<std::string> gemCounts = {"3", "5", "8", "6", "9"};
    int moveCount = 30;
    bool vertical;
    bool horizontal;

    void initBoard();
    void loadResources();
    void random();
    void createGems();
    void swapGems(int, int, int, int);

public:
    Board(sf::RenderWindow* window, int x, int y, int w, int h, sf::Vector2i offset, int holes);
    ~Board();
    void update();
    void render();
    void updateSFMLEvents();
    void updateMouseClickedPos(sf::Vector2i);
    void updateMouseReleasedPos(sf::Vector2i);

};


#endif //MATCH3GAME_BOARD_H
