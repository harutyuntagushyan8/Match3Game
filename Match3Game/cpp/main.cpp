
#include "Game.h"
#include "ResourcePath.hpp"

int main(int, char const**) {
    Game game = Game::getInstance();
    game.run();
}
