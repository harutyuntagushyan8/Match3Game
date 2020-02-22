//
// Created by Harutyun Tagushyan on 2020-02-05.
// Copyright (c) 2020 Harutyun Tagushyan. All rights reserved.
//

#include "Board.h"
#include "ResourcePath.hpp"
#include <iostream>
#include <cmath>

Board::~Board() {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            delete gems[i][j];
        }
    }
}

Board::Board(sf::RenderWindow* window, int x, int y, int r, int c, sf::Vector2i offset, int holeCount) :
                        window(window), originX(x), originY(y), rows(r), columns(c), offset(offset), holeCount(holeCount) {
    initScoredGems();
    initBoard();
    loadResources();
    random();
    createGems();
}

void Board::initScoredGems() {
    font.loadFromFile(resourcePath() + "Sansation_Italic.ttf");
    float x = 10.0f;
    for(int i = 0; i < gemCounts.size(); ++i) {
        gemsCountsText.push_back(sf::Text());
        gemsCountsText[i].setFont(font);
        gemsCountsText[i].setFillColor(sf::Color::White);
        gemsCountsText[i].setString(std::to_string(gemCounts[i].second));
        gemsCountsText[i].setCharacterSize(60);
        gemsCountsText[i].setPosition(x + 10, 80);
        x += 100.0f;
    }
    scoreText.setFont(font);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString(std::to_string(scoreValue));
    scoreText.setCharacterSize(100);
    scoreText.setPosition(510 + 200/2 - scoreText.getLocalBounds().width/2, 10);
}

void Board::initBoard() {
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

void Board::random() {
    holes.resize(holeCount);
    for(int i = 0; i < holeCount; ++i) {
        holes[i] = std::rand() % (rows * columns);
    }
}

void Board::update() {
    updateSFMLEvents();
    checkGemSwapping();
    while(checkSimpleMatch()) {
        updateScoredGems();
        resetMatches();
    }
    if(sumOfScores() == 0 && scoreValue > 0) {
        std::cout << "You win the game\n";
    }
}

int Board::sumOfScores() {
    int sumOfScores = 0;
    for(int i = 0; i < gemCounts.size(); ++i) {
        sumOfScores += gemCounts[i].second;
    }
    return sumOfScores;
}

void Board::updateMouseClickedPos(sf::Vector2i pos) {
    clickedPos = pos;
}

void Board::updateMouseReleasedPos(sf::Vector2i pos) {
    releasedPos = pos;
}

void Board::checkGemSwapping() {
    int firstRow = (clickedPos.y - originY)/offset.y;
    int firstColumn = (clickedPos.x - originX)/offset.x;
    int secondRow = (releasedPos.y - originY)/offset.y;
    int secondColumn = (releasedPos.x - originX)/offset.x;
    if(secondRow == firstRow && secondColumn == firstColumn) {
        return;
    }
    int deltaX = clickedPos.x - releasedPos.x;
    int deltaY = clickedPos.y - releasedPos.y;
    if((std::abs(deltaX) <= offset.x && firstRow == secondRow) ||
        (std::abs(deltaY) <= offset.y && firstColumn == secondColumn)) {
        swapGems(firstRow, firstColumn, secondRow, secondColumn);
        if(!checkSimpleMatch()) {
            swapGems(secondRow, secondColumn, firstRow, firstColumn);
        }
    }
}

void Board::render() {
    window->draw(scoreText);
    for(int i = 0; i < gemsCountsText.size(); ++i) {
        window->draw(gemsCountsText[i]);
    }
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j)
            gems[i][j]->render();
    }
}

void Board::updateSFMLEvents() {

}

void Board::createGems() {
    srand((int) time(0));
    bool tileSequence = true;
    int x = originX;
    int y = originY;
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if(std::find(holes.begin(), holes.end(), i * rows + j) == holes.end()) {
                int randomGem = std::rand() % gemIcons.size();
                if(tileSequence) {
                    gems[i][j] = new Gem(window, x, y, i, j, offset, static_cast<GemType>(randomGem), tile1, randomGem, gemTextures[randomGem]);
                } else {
                    gems[i][j] = new Gem(window, x, y, i, j, offset, static_cast<GemType>(randomGem), tile2, randomGem, gemTextures[randomGem]);
                }
                x += offset.x;
                if(columns%2 == 0 || (columns%2 != 0 && j != columns - 1))
                    tileSequence = !tileSequence;
            } else {
                gems[i][j] = new Gem(window, x, y, i, j, offset, GemType::SolidColor, nullptr, 5, nullptr);
                x += offset.x;
                if(columns%2 == 0 || (columns%2 != 0 && j != columns - 1))
                    tileSequence = !tileSequence;
            }
        }
        tileSequence = !tileSequence;
        x = originX;
        y += offset.y;
    }
    while(checkSimpleMatch()) {

    }
    checkSimpleMatch();
}

void Board::swapGems(int firstRow, int firstColumn, int secondRow, int secondColumn) {
    if(std::find(holes.begin(), holes.end(), firstRow * columns + firstColumn) == holes.end() &&
            std::find(holes.begin(), holes.end(), secondRow * columns + secondColumn) == holes.end()) {

        int tempGemNumber = gems[firstRow][firstColumn]->gemNumber;
        gems[firstRow][firstColumn]->gemNumber = gems[secondRow][secondColumn]->gemNumber;
        gems[secondRow][secondColumn]->gemNumber = tempGemNumber;

        GemType tempType = gems[firstRow][firstColumn]->type;
        gems[firstRow][firstColumn]->type = gems[secondRow][secondColumn]->type;
        gems[secondRow][secondColumn]->type = tempType;

        gems[firstRow][firstColumn]->setGemTexture(gemTextures[gems[firstRow][firstColumn]->gemNumber]);
        gems[secondRow][secondColumn]->setGemTexture(gemTextures[gems[secondRow][secondColumn]->gemNumber]);
    }
}

bool Board::checkSimpleMatch() {
    for(int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < columns - 1; ++j) {
            if (gems[i][j]->type == gems[i - 1][j]->type) {
                if (gems[i][j]->type == gems[i + 1][j]->type) {
                    for (int k = -1; k <= 1; ++k) {
                        gems[i + k][j]->matchCount++;
                    }
                    updateScoredGems();
                    resetMatches();
                    for (int k = -1; k <= 1; ++k) {
                        int randomGem = std::rand() % gemIcons.size();
                        gems[i + k][j]->setGemTexture(gemTextures[randomGem]);
                        gems[i + k][j]->setGemType(static_cast<GemType>(randomGem));
                        gems[i + k][j]->gemNumber = randomGem;
                    }
                    if (scoreValue != 0)
                        scoreText.setString(std::to_string(--scoreValue));
                    return true;
                }
            }

            if (gems[i][j]->type == gems[i][j - 1]->type) {
                if (gems[i][j]->type == gems[i][j + 1]->type) {
                    for (int k = -1; k <= 1; ++k) {
                        gems[i][j + k]->matchCount++;
                    }
                    updateScoredGems();
                    resetMatches();
                    for (int k = -1; k <= 1; ++k) {
                        int randomGem = std::rand() % gemIcons.size();
                        gems[i][j + k]->setGemTexture(gemTextures[randomGem]);
                        gems[i][j + k]->setGemType(static_cast<GemType>(randomGem));
                        gems[i][j + k]->gemNumber = randomGem;
                    }
                    if (scoreValue != 0)
                        scoreText.setString(std::to_string(--scoreValue));
                    return true;
                }
            }
        }
    }
    // Must check perimeter of board(first row)
    for(int j = 1; j < columns - 1; ++j) {
        if(gems[0][j]->type == gems[0][j - 1]->type) {
            if(gems[0][j]->type == gems[0][j + 1]->type) {
                for (int k = -1; k <= 1; ++k) {
                    gems[0][j + k]->matchCount++;
                }
                updateScoredGems();
                resetMatches();
                for (int k = -1; k <= 1; ++k) {
                    int randomGem = std::rand() % gemIcons.size();
                    gems[0][j + k]->setGemTexture(gemTextures[randomGem]);
                    gems[0][j + k]->setGemType(static_cast<GemType>(randomGem));
                    gems[0][j + k]->gemNumber = randomGem;
                }
                if (scoreValue != 0)
                    scoreText.setString(std::to_string(--scoreValue));
                return true;
            }
        }
    }
    // last row
    for(int j = 1; j < columns - 1; ++j) {
        if(gems[rows - 1][j]->type == gems[rows - 1][j - 1]->type) {
            if(gems[rows - 1][j]->type == gems[rows - 1][j + 1]->type) {
                for (int k = -1; k <= 1; ++k) {
                    gems[rows - 1][j + k]->matchCount++;
                }
                updateScoredGems();
                resetMatches();
                for (int k = -1; k <= 1; ++k) {
                    int randomGem = std::rand() % gemIcons.size();
                    gems[rows - 1][j + k]->setGemTexture(gemTextures[randomGem]);
                    gems[rows - 1][j + k]->setGemType(static_cast<GemType>(randomGem));
                    gems[rows - 1][j + k]->gemNumber = randomGem;
                }
                if (scoreValue != 0)
                    scoreText.setString(std::to_string(--scoreValue));
                return true;
            }
        }
    }
    // first column
    for(int i = 1; i < rows - 1; ++i) {
        if(gems[i][0]->type == gems[i - 1][0]->type) {
            if(gems[i][0]->type == gems[i + 1][0]->type) {
                for (int k = -1; k <= 1; ++k) {
                    gems[i + k][0]->matchCount++;
                }
                updateScoredGems();
                resetMatches();
                for (int k = -1; k <= 1; ++k) {
                    int randomGem = std::rand() % gemIcons.size();
                    gems[i + k][0]->setGemTexture(gemTextures[randomGem]);
                    gems[i + k][0]->setGemType(static_cast<GemType>(randomGem));
                    gems[i + k][0]->gemNumber = randomGem;
                }
                if (scoreValue != 0)
                    scoreText.setString(std::to_string(--scoreValue));
                return true;
            }
        }
    }
    // last column
    for(int i = 1; i < rows - 1; ++i) {
        if(gems[i][columns - 1]->type == gems[i - 1][columns - 1]->type) {
            if(gems[i][columns - 1]->type == gems[i + 1][columns - 1]->type) {
                for (int k = -1; k <= 1; ++k) {
                    gems[i + k][columns - 1]->matchCount++;
                }
                updateScoredGems();
                resetMatches();
                for (int k = -1; k <= 1; ++k) {
                    int randomGem = std::rand() % gemIcons.size();
                    gems[i + k][columns - 1]->setGemTexture(gemTextures[randomGem]);
                    gems[i + k][columns - 1]->setGemType(static_cast<GemType>(randomGem));
                    gems[i + k][columns - 1]->gemNumber = randomGem;
                }
                if (scoreValue != 0)
                    scoreText.setString(std::to_string(--scoreValue));
                return true;
            }
        }
    }
    return false;
}

bool Board::check4Match() {
    return false;
}

bool Board::checkSquareMatch() {
    return false;
}

void Board::updateScoredGems() {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if(gems[i][j]->matchCount != 0) {
                switch (gems[i][j]->type) {
                    case GemType::Blue :    if(gemCounts[0].second > 0)
                                                --gemCounts[0].second;
                                            break;
                    case GemType::Green :   if(gemCounts[1].second > 0)
                                                --gemCounts[1].second;
                                            break;
                    case GemType::Orange :  if(gemCounts[2].second > 0)
                                                --gemCounts[2].second;
                                            break;
                    case GemType::Red :     if(gemCounts[3].second > 0)
                                                --gemCounts[3].second;
                                            break;
                    case GemType::Violet :  if(gemCounts[4].second > 0)
                                                --gemCounts[4].second;
                                            break;
                    default:
                        break;
                }
            }
        }
    }
    for(int i = 0; i < gemsCountsText.size(); ++i) {
        gemsCountsText[i].setString(std::to_string(gemCounts[i].second));
    }
}

void Board::resetMatches() {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            gems[i][j]->matchCount = 0;
        }
    }
}

