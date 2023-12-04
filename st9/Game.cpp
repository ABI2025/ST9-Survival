#include "Game.h"

Game* Game::erstelleGame() {
    if (!game) {
        game = new Game();
    }
    return game;
}
void Game::setMap(Utils::Cell& cell, int x, int y, int z) {
    /*if (x >= 0 && x < map.size() &&
        y >= 0 && y < map[x].size() &&
        z >= 0 && z < map[x][y].size()) {
        map[x][y][z] = cell;
    } 
    else {
        std::cout << "oh No Anyways";
    }*/
    map[x][y][z] = cell;
}
std::vector<std::vector<std::vector<Utils::Cell>>>& Game::getMap() {
    return map;
}