#include "Game.h"

Game* Game::erstelleGame() {
    if (!s_game) 
        s_game = new Game();
    return s_game;
}
void Game::setMap(Utils::Cell& cell, int x, int y, int z) {
    if (
        z < m_map.size() && z >= 0 &&
        y < m_map[z].size() && y >= 0 &&
        x < m_map[z][y].size() && x >= 0
        )
        m_map[z][y][x] = cell;
    else
        LOG_ERROR("index [{}][{}][{}] is not valid",z,y,x);
}
std::vector<std::vector<std::vector<Utils::Cell>>>& Game::get_map() {
    return m_map;
}