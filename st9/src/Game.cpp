#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <imgui.h>
#include "Camera.h"
#include "imgui-SFML.h"
#include "Player.h"

Game::Game() 
{
    background_textures.resize(4);
    if (!background_textures[0].loadFromFile("Resources/Background1.jpg"))throw std::exception("Du hurensohn");
    if (!background_textures[1].loadFromFile("Resources/Background2.jpg"))throw std::exception("Du hurensohn");
    if (!background_textures[2].loadFromFile("Resources/Background3.jpg"))throw std::exception("Du hurensohn");
    if (!background_textures[3].loadFromFile("Resources/Background4.jpg"))throw std::exception("Du hurensohn");

    background_sprites[0].setTexture(background_textures[0]);
    background_sprites[1].setTexture(background_textures[1]);
    background_sprites[2].setTexture(background_textures[2]);
    background_sprites[3].setTexture(background_textures[3]);

}

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

int Game::renderMap(sf::RenderWindow& window)
{
    

    window.draw(background_sprites[0]);
    window.draw(background_sprites[1]);
    window.draw(background_sprites[2]);
    window.draw(background_sprites[3]);
    
}

constexpr int height = 10;
constexpr int width = 10;



std::vector<std::vector<uint8_t[2]>> erstelleMap() 
{
    std::vector<std::vector<uint8_t[2]>> KARTE;
    uint8_t kk[2] = {0,0};
    for (int i = 0; i < width; i++)
    {
        std::vector<uint8_t[2]> inner_map;
        for (int j = 0; j < height; j++) 
        {
            kk[0] = Utils::Random::UInt(0, 3);
            inner_map.emplace_back(kk);
        
        }
        KARTE.emplace_back(inner_map);
    }
    return KARTE;
}
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