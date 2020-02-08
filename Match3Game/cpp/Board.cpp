//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Board.h"
#include "ResourcePath.hpp"

Board::Board(sf::RenderWindow* window, int x, int y, int r, int c, sf::Vector2i offset, int holeCount) :
                        window(window), originX(x), originY(y), rows(r), columns(c), offset(offset), holeCount(holeCount) {
    initBoard();
    loadResources();
    random();
    createGems();
}

void Board::initBoard() {
    tile1 = new sf::Texture;
    tile2 = new sf::Texture;
    h_bomb = new sf::Texture;
    v_bomb = new sf::Texture;
    bomb = new sf::Texture;
    gems.resize(rows, std::vector<Gem*>(columns));
    //menuGems.resize(gemIcons.size());
    //gemTextures.resize(gemIcons.size());
    for(int i = 0; i < gemIcons.size(); ++i) {
        gemTextures.push_back(new sf::Texture());
    }
    for(int i = 0; i < gemIcons.size(); ++i) {
        menuGems.push_back(sf::Sprite());
    }
}

void Board::loadResources() {
    tile1->loadFromFile(resourcePath() + "tile_1.png");
    tile2->loadFromFile(resourcePath() + "tile_2.png");
    h_bomb->loadFromFile(resourcePath() + "h_bomb.png");
    v_bomb->loadFromFile(resourcePath() + "v_bomb.png");
    bomb->loadFromFile(resourcePath() + "bomb.png");
    for(int i = 0; i < gemIcons.size(); ++i) {
        gemTextures[i]->loadFromFile(resourcePath() + gemIcons[i]);
    }
    for(int i = 0; i < gemIcons.size(); ++i) {
        menuGems.push_back(sf::Sprite());
        menuGems[i].setTexture(*gemTextures[i]);
    }
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
                int randomGem = std::rand() % gemIcons.size();
                if(tileSequence) {
                    gems[i][j] = new Gem(window, x, y, offset, tile1, gemTextures[randomGem]);
                } else {
                    gems[i][j] = new Gem(window, x, y, offset, tile2, gemTextures[randomGem]);
                }
                x += offset.x;
                tileSequence = !tileSequence;
            } else {
                tileSequence = !tileSequence;
                x += offset.x;
            }
        }
        tileSequence = !tileSequence;
        x = originX;
        y += offset.y;
    }
}



