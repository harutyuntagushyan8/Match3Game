//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Board.h"

Board::Board(sf::RenderWindow* window, int x, int y, int r, int c, sf::Vector2i offset, int holeCount) :
                        window(window), originX(x), originY(y), rows(r), columns(c), offset(offset), holeCount(holeCount) {
    tile1 = new sf::Texture;
    tile2 = new sf::Texture;
    h_bomb = new sf::Texture;
    v_bomb = new sf::Texture;
    gems.resize(rows, std::vector<Gem*>(columns));
    gemTextures.resize(gemIcons.size());
    for(int i = 0; i < gemTextures.size(); ++i) {
        gemTextures[i] = new sf::Texture;
    }
    random();
    loadResources();
    createGems();

}

void Board::update() {

}

void Board::render() {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j)
            if(std::find(holes.begin(), holes.end(), i * rows + j) == holes.end()) {
                gems[i][j]->render();
            }
    }
}

void Board::updateSFMLEvents() {

}

Board::~Board() {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            delete gems[i][j];
        }
    }
}

void Board::random() {
    holes.resize(holeCount);
    for(int i = 0; i < holeCount; ++i) {
        holes[i] = std::rand() % (rows * columns);
    }
}

void Board::createGems() {
    bool tileSequence = true;
    int x = originX;
    int y = originY;
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if(std::find(holes.begin(), holes.end(), i * rows + j) == holes.end()) {
                int randomGem = std::rand() % gemTextures.size();
                if(tileSequence) {
                    gems[i][j] = new Gem(window, x, y, offset, tile1, gemTextures[randomGem]);
                    tileSequence = false;
                    x += offset.x;
                } else {
                    gems[i][j] = new Gem(window, x, y, offset, tile2, gemTextures[randomGem]);
                    tileSequence = true;
                    x += offset.x;
                }
            } else {
                if(tileSequence)
                    tileSequence = false;
                else
                    tileSequence = true;
                x += offset.x;
            }
        }
        x = originX;
        y += offset.y;
    }
}

void Board::loadResources() {
    try {
        tile1->loadFromFile(resourcePath() + "tile_1.png");
        tile2->loadFromFile(resourcePath() + "tile_2.png");
        h_bomb->loadFromFile(resourcePath() + "h_bomb.png");
        v_bomb->loadFromFile(resourcePath() + "v_bomb.png");
        for(int i = 0; i < gemTextures.size(); ++i) {
            gemTextures[i]->loadFromFile(resourcePath() + "blue.png");
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << "\n";
    }
}
