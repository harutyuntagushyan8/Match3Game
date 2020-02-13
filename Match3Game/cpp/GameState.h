//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_GAMESTATE_H
#define MATCH3GAME_GAMESTATE_H

#include "State.h"
#include "Board.h"


class GameState : public State {
private:
    void initWindow();
    void loadResources();

    // Variables
    Board* board;
    sf::RectangleShape mainShape;
    sf::RectangleShape shapeForMoveCount;
    std::vector<sf::Sprite> menuGems;
    sf::Vector2i clickedPos;
    sf::Vector2i releasedPos;
    std::vector<sf::Texture*> gemTextures;
    sf::Texture* tile1, *tile2, *h_bomb, *v_bomb, *bomb;
    std::vector<std::string> gemIcons = {"blue.png", "green.png", "orange.png", "red.png", "violet.png"};

    const int ROWS = 6;
    const int COLUMNS = 6;
    const int HOLESCOUNT = 3;
    const int X = 300;
    const int Y = 300;
    const sf::Vector2i OFFSET{150, 150};

public:
    GameState(sf::RenderWindow* window);
    void updateSFMLEvents();
    void update();
    void render();
};

#endif //MATCH3GAME_GAMESTATE_H
