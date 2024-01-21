#include "Game.h"
#include "Player.h"
#include "camera.h"
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

void Game::runGame(int) {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
}