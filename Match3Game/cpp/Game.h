//
// Created by Harutyun Tagushyan on 2020-02-02.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#ifndef MATCH3GAME_GAME_H
#define MATCH3GAME_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "Board.h"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const int ROWS = 10;
const int COLUMNS = 10;
const int HOLESCOUNT = 3;
const int X = 50;
const int Y = 50;

class Game {
private:
    void initWindow();
    void updateSFMLEvents();
    void update();
    void render();

    // Variables
    sf::RenderWindow* window;
    sf::Event sfEvent;
    Board* board;
    sf::Image icon;
    sf::Music music;
    sf::Vector2f mousePos;

public:
    Game();
    virtual ~Game();
    void run();

};

#endif //MATCH3GAME_GAME_H
