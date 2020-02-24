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
//    std::cout << "After update\n";
//    for(int i = 0; i < rows; ++i) {
//        for(int j = 0; j < columns; ++j) {
//            std::cout << static_cast<std::underlying_type<GemType >::type>(gems[i][j]->type) <<
//                      static_cast<std::underlying_type<GemType >::type>(gems[i][j]->bombType) << gems[i][j]->gemNumber << "  ";
//        }
//        std::cout << "\n\n";
//    }
//    std::cout << "\n\n";
    if(sumOfScores() == 0 && scoreValue > 0) {
        scoreText.setString("Win");
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
        bool match_4 = check4Match();
        if(match_4) {
            if(isHorizontalBomb) {
                isHorizontalBomb = false;
                return;
            }
            if(isVerticalBomb) {
                isVerticalBomb = false;
                return;
            }
        } else {
            if(!checkSimpleMatch()) {
                swapGems(secondRow, secondColumn, firstRow, firstColumn);
            }
        }
//        std::cout << "After correct match\n";
//        for(int i = 0; i < rows; ++i) {
//            for(int j = 0; j < columns; ++j) {
//                std::cout << static_cast<std::underlying_type<GemType >::type>(gems[i][j]->type) <<
//                        static_cast<std::underlying_type<GemType >::type>(gems[i][j]->bombType) << gems[i][j]->gemNumber << "  ";
//            }
//            std::cout << "\n\n";
//        }
//        std::cout << "\n\n";
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
                gems[i][j] = new Gem(window, x, y, i, j, offset, GemType::SolidColor, nullptr, static_cast<int>(GemType::SolidColor), nullptr);
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
//    std::cout << "After create board\n";
//    for(int i = 0; i < rows; ++i) {
//        for(int j = 0; j < columns; ++j) {
//            std::cout << static_cast<std::underlying_type<GemType >::type>(gems[i][j]->type) <<
//                      static_cast<std::underlying_type<GemType >::type>(gems[i][j]->bombType) << gems[i][j]->gemNumber << "  ";
//        }
//        std::cout << "\n\n";
//    }
//    std::cout << "\n\n";
}

void Board::swapGems(int firstRow, int firstColumn, int secondRow, int secondColumn) {
    if(std::find(holes.begin(), holes.end(), firstRow * columns + firstColumn) == holes.end() &&
            std::find(holes.begin(), holes.end(), secondRow * columns + secondColumn) == holes.end()) {

        if (gems[firstRow][firstColumn]->bombType == BombType::HorizontalBomb || gems[firstRow][firstColumn]->bombType == BombType::VerticalBomb ||
                gems[secondRow][secondColumn]->bombType == BombType::HorizontalBomb || gems[secondRow][secondColumn]->bombType == BombType::VerticalBomb) {
            return;
        }
        int tempGemNumber = gems[firstRow][firstColumn]->gemNumber;
        gems[firstRow][firstColumn]->gemNumber = gems[secondRow][secondColumn]->gemNumber;
        gems[secondRow][secondColumn]->gemNumber = tempGemNumber;

        GemType tempType = gems[firstRow][firstColumn]->type;
        gems[firstRow][firstColumn]->type = gems[secondRow][secondColumn]->type;
        gems[secondRow][secondColumn]->type = tempType;

        gems[firstRow][firstColumn]->setGemTexture(gemTextures[gems[firstRow][firstColumn]->gemNumber]);
        gems[secondRow][secondColumn]->setGemTexture(gemTextures[gems[secondRow][secondColumn]->gemNumber]);
        std::cout << "After swapping\n";
//        for(int i = 0; i < rows; ++i) {
//            for(int j = 0; j < columns; ++j) {
//                std::cout << static_cast<std::underlying_type<GemType >::type>(gems[i][j]->type) <<
//                          static_cast<std::underlying_type<GemType >::type>(gems[i][j]->bombType) << gems[i][j]->gemNumber << "  ";
//            }
//            std::cout << "\n\n";
//        }
//        std::cout << "\n\n";
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
    for(int i = 1; i < rows - 2; ++i) {
        for (int j = 1; j < columns - 2; ++j) {
            if (gems[i][j]->type == gems[i - 1][j]->type) {
                if (gems[i][j]->type == gems[i + 1][j]->type) {
                    if(gems[i][j]->type == gems[i + 2][j]->type) {
                        isVerticalBomb = true;
                        int bombRow = (clickedPos.y - originY)/offset.y;
                        gems[bombRow][j]->setGemTexture(v_bomb);
                        gems[bombRow][j]->setGemType(GemType::Undefined);
                        gems[bombRow][j]->setBombType(BombType::VerticalBomb);
                        gems[bombRow][j]->gemNumber = static_cast<int>(GemType::Undefined);
                        return true;
                    }
                }
            }

            if (gems[i][j]->type == gems[i][j - 1]->type) {
                if (gems[i][j]->type == gems[i][j + 1]->type) {
                    if (gems[i][j]->type == gems[i][j + 2]->type) {
                        isHorizontalBomb = true;
                        int bombColumn = (clickedPos.x - originX)/offset.x;
                        gems[i][bombColumn]->setGemTexture(h_bomb);
                        gems[i][bombColumn]->setGemType(GemType::Undefined);
                        gems[i][bombColumn]->setBombType(BombType::HorizontalBomb);
                        gems[i][bombColumn]->gemNumber = static_cast<int>(GemType::Undefined);
                        return true;
                    }
                }
            }
        }
    }
    // Must check perimeter of board(first row)
    for(int j = 1; j < columns - 2; ++j) {
        if(gems[0][j]->type == gems[0][j - 1]->type ) {
            if(gems[0][j]->type == gems[0][j + 1]->type) {
                if (gems[0][j]->type == gems[0][j + 2]->type) {
                    isHorizontalBomb = true;
                    int bombColumn = (clickedPos.x - originX)/offset.x;
                    gems[0][bombColumn]->setGemTexture(h_bomb);
                    gems[0][bombColumn]->setGemType(GemType::Undefined);
                    gems[0][bombColumn]->setBombType(BombType::HorizontalBomb);
                    gems[0][bombColumn]->gemNumber = static_cast<int>(GemType::Undefined);
                    return true;
                }
            }
        }
    }
    // last row
    for(int j = 1; j < columns - 2; ++j) {
        if(gems[rows - 1][j]->type == gems[rows - 1][j - 1]->type) {
            if(gems[rows - 1][j]->type == gems[rows - 1][j + 1]->type) {
                if (gems[rows - 1][j]->type == gems[rows - 1][j + 2]->type) {
                    isHorizontalBomb = true;
                    int bombColumn = (clickedPos.x - originX)/offset.x;;
                    gems[rows - 1][bombColumn]->setGemTexture(h_bomb);
                    gems[rows - 1][bombColumn]->setGemType(GemType::Undefined);
                    gems[rows - 1][bombColumn]->setBombType(BombType::HorizontalBomb);
                    gems[rows - 1][bombColumn]->gemNumber = static_cast<int>(GemType::Undefined);
                    return true;
                }
            }
        }
    }
    // first column
    for(int i = 1; i < rows - 2; ++i) {
        if(gems[i][0]->type == gems[i - 1][0]->type) {
            if(gems[i][0]->type == gems[i + 1][0]->type) {
                if (gems[i][0]->type == gems[i + 2][0]->type) {
                    isVerticalBomb = true;
                    int bombRow = (clickedPos.y - originY)/offset.y;
                    gems[bombRow][0]->setGemTexture(v_bomb);
                    gems[bombRow][0]->setGemType(GemType::Undefined);
                    gems[bombRow][0]->setBombType(BombType::VerticalBomb);
                    gems[bombRow][0]->gemNumber = static_cast<int>(GemType::Undefined);
                    return true;
                }
            }
        }
    }
    // last column
    for(int i = 1; i < rows - 2; ++i) {
        if(gems[i][columns - 1]->type == gems[i - 1][columns - 1]->type) {
            if(gems[i][columns - 1]->type == gems[i + 1][columns - 1]->type) {
                if (gems[i][columns - 1]->type == gems[i + 2][columns - 1]->type) {
                    isVerticalBomb = true;
                    int bombRow = (clickedPos.y - originY)/offset.y;
                    gems[bombRow][columns - 1]->setGemTexture(v_bomb);
                    gems[bombRow][columns - 1]->setGemType(GemType::Undefined);
                    gems[bombRow][columns - 1]->setBombType(BombType::VerticalBomb);
                    gems[bombRow][columns - 1]->gemNumber = static_cast<int>(GemType::Undefined);
                    return true;
                }
            }
        }
    }
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

void Board::explodeBomb() {
    int clickRow = std::abs((clickedPos.y - originY)/offset.y);
    int clickColumn = std::abs((clickedPos.x - originX)/offset.x);
    if (gems[clickRow][clickColumn]->bombType == BombType::HorizontalBomb) {
        for(int j = 0; j < columns; ++j) {
            if (gems[clickRow][j]->type != GemType::SolidColor) {
                if (gems[clickRow][j]->bombType == BombType ::Undefined)
                    gems[clickRow][j]->matchCount++;
                updateScoredGems();
                resetMatches();
                int randomGem = std::rand() % gemIcons.size();
                gems[clickRow][j]->setGemTexture(gemTextures[randomGem]);
                gems[clickRow][j]->setGemType(static_cast<GemType>(randomGem));
                gems[clickRow][j]->gemNumber = randomGem;
                gems[clickRow][j]->bombType = BombType::Undefined;
                if (scoreValue != 0)
                    scoreText.setString(std::to_string(--scoreValue));
            }
        }
    }
    else if (gems[clickRow][clickColumn]->bombType == BombType::VerticalBomb) {
        for(int i = 0; i < rows; ++i) {
            if (gems[i][clickColumn]->type != GemType::SolidColor) {
                if (gems[i][clickColumn]->bombType == BombType ::Undefined)
                    gems[i][clickColumn]->matchCount++;
                updateScoredGems();
                resetMatches();
                int randomGem = std::rand() % gemIcons.size();
                gems[i][clickColumn]->setGemTexture(gemTextures[randomGem]);
                gems[i][clickColumn]->setGemType(static_cast<GemType>(randomGem));
                gems[i][clickColumn]->gemNumber = randomGem;
                gems[i][clickColumn]->bombType = BombType::Undefined;
                if (scoreValue != 0)
                    scoreText.setString(std::to_string(--scoreValue));
            }
        }
    } else {

    }
}

bool Board::isBoardHasBomb() {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if (gems[i][j]->bombType == BombType::VerticalBomb || gems[i][j]->bombType == BombType::HorizontalBomb)
                return true;
        }
    }
    return false;
}

