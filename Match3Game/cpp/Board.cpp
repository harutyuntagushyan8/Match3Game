//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Board.h"

Board::Board(int x, int y, int r, int c, int holeCount) : originX(x), originY(y), rows(r), columns(c) {
    gems.reserve(rows);
    for(int i = 0; i < rows; ++i) {
        gems[i].reserve(columns);
    }
    this->holeCount = holeCount;
    random();
    loadResources();
    createGems();

}

int Board::getRows() {
    return rows;
}

int Board::getColumns() {
    return columns;
}

void Board::update() {

}

void Board::render() {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j)
            gems[i][j]->render();
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
    holes = new int[holeCount];
    for(int i = 0; i < holeCount; ++i) {
        holes[i] = std::rand() % (rows * columns);
    }
}

void Board::createGems() {
    bool tileSequence = true;
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            for(int index = 0; index < holeCount; ++index) {
                if(i * rows + j != holes[index]) {
                    int randomGem = std::rand() % gemIcons.size();
                    if(tileSequence) {
                        //gems[i][j] = new Gem(tile1, gemTextures[1]);
                        tileSequence = false;
                    } else {
                        //gems[i][j] = new Gem(tile2, gemTextures[1]);
                        tileSequence = true;
                    }
                }
            }

        }
    }
}

void Board::loadResources() {
    try {
        tile1->loadFromFile(resourcePath() + "tile_1.png");
        tile2->loadFromFile(resourcePath() + "tile_2.png");
        h_bomb->loadFromFile(resourcePath() + "h_bomb.png");
        v_bomb->loadFromFile(resourcePath() + "v_bomb.png");
    }
    catch (std::exception& e) {
        std::cout << e.what() << "\n";
    }
    sprite1->setTexture(*tile1);
    sprite2->setTexture(*tile2);
    sprite_h_bomb->setTexture(*h_bomb);
    sprite_v_bomb->setTexture(*v_bomb);
    for(int i = 0; i < gemTextures.size(); ++i) {
        gemTextures[i]->loadFromFile(resourcePath() + gemIcons[i]);
        gemSprites[i]->setTexture(*gemTextures[i]);
    }
}
