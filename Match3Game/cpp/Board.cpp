//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Board.h"
#include "ResourcePath.hpp"
#include <iostream>
#include <cmath>

Board::Board(sf::RenderWindow* window, int x, int y, int r, int c, sf::Vector2i offset, int holeCount) :
                        window(window), originX(x), originY(y), rows(r), columns(c), offset(offset), holeCount(holeCount) {
    initBoard();
    loadResources();
    random();
    createGems();
}

void Board::initBoard() {
    click = 0;
    tile1 = new sf::Texture;
    tile2 = new sf::Texture;
    h_bomb = new sf::Texture;
    v_bomb = new sf::Texture;
    bomb = new sf::Texture;
    gems.resize(rows, std::vector<Gem*>(columns));
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
    updateSFMLEvents();
}

void Board::updateMouseClickedPos(sf::Vector2i pos) {
    clickedPos = pos;
    std::cout << "Board Click ";
    std::cout << "x = " << clickedPos.x << " y = " << clickedPos.y << "\n";
}

void Board::updateMouseReleasedPos(sf::Vector2i pos) {
    releasedPos = pos;
    std::cout << "Board Release ";
    std::cout << "x = " << releasedPos.x << " y = " << releasedPos.y << "\n";
    if(std::abs(clickedPos.x - releasedPos.x) <= 150 || std::abs(clickedPos.y - releasedPos.y) <= 150) {
        int firstRow = (clickedPos.y - originY)/offset.y;
        int firstColumn = (clickedPos.x - originX)/offset.x;
        int secondRow = (releasedPos.y - originY)/offset.y;
        int secondColumn = (releasedPos.x - originX)/offset.x;
        swapGems(firstRow, firstColumn, secondRow, secondColumn);
    }
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
                    gems[i][j] = new Gem(window, x, y, i, j, offset, tile1, randomGem, gemTextures[randomGem]);
                } else {
                    gems[i][j] = new Gem(window, x, y, i, j, offset, tile2, randomGem, gemTextures[randomGem]);
                }
                x += offset.x;
                if(columns%2 == 0)
                    tileSequence = !tileSequence;
                else if(columns%2 != 0 && j != columns - 1)
                    tileSequence = !tileSequence;
            } else {
                if(columns%2 == 0)
                    tileSequence = !tileSequence;
                else if(columns%2 != 0 && j != columns - 1)
                    tileSequence = !tileSequence;
                x += offset.x;
            }
        }
        tileSequence = !tileSequence;
        x = originX;
        y += offset.y;
    }
}

void Board::swapGems(int firstRow, int firstColumn, int secondRow, int secondColumn) {
    if(std::find(holes.begin(), holes.end(), firstRow * columns + firstColumn) == holes.end() &&
            std::find(holes.begin(), holes.end(), secondRow * columns + secondColumn) == holes.end()) {
        gems[firstRow][firstColumn]->setGem(gemTextures[gems[secondRow][secondColumn]->gemNumber]);
        gems[secondRow][secondColumn]->setGem(gemTextures[gems[firstRow][firstColumn]->gemNumber]);
        int tempGemNumber = gems[firstRow][firstColumn]->gemNumber;
        gems[firstRow][firstColumn]->gemNumber = gems[secondRow][secondColumn]->gemNumber;
        gems[secondRow][secondColumn]->gemNumber = tempGemNumber;
    }
}



