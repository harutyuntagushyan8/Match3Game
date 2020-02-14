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
#include "State.h"
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
    sf::Vector2i offset;
    std::vector<std::vector<Gem*>> gems;
    std::vector<int> holes;
    int holeCount;
    sf::Vector2i releasedPos;
    sf::Vector2i clickedPos;
    sf::Font font;
    sf::Text scoreText;
    int scoreValue = 20;
    std::vector<sf::Text> gemsCountsText;
    std::vector<sf::Sprite> menuGems;
    std::vector<sf::Texture*> gemTextures;
    sf::Texture* tile1, *tile2, *h_bomb, *v_bomb, *bomb;
    std::vector<std::string> gemIcons = {"blue.png", "green.png", "orange.png", "red.png", "violet.png"};
    std::vector<std::pair<GemType, int>> gemCounts = {std::make_pair(GemType::Blue,3), std::make_pair(GemType::Green,5), std::make_pair(GemType::Orange,8),
                                                        std::make_pair(GemType::Red,6), std::make_pair(GemType::Violet,9)};

    void initBoard();
    void initScoredGems();
    void checkGemSwapping();
    bool checkSimpleMatch();
    void resetMatches();
    void updateScoredGems();
    bool check4Match();
    bool checkSquareMatch();
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
