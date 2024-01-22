#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <imgui.h>
#include "Camera.h"
#include "imgui-SFML.h"
#include "Player.h"

Game::Game(sf::RenderWindow& window):m_window(window)
{
    window.setFramerateLimit(60);
    background_textures.resize(4);

	if (!background_textures[0].loadFromFile("Resources/Background1.jpg"))throw std::exception("Fehler");
    if (!background_textures[1].loadFromFile("Resources/Background2.jpg"))throw std::exception("Fehler");
    if (!background_textures[2].loadFromFile("Resources/Background3.jpg"))throw std::exception("Fehler");
    if (!background_textures[3].loadFromFile("Resources/Background4.jpg"))throw std::exception("Fehler");

	background_sprites.resize(4);

	background_sprites[0].setTexture(background_textures[0]);
    background_sprites[1].setTexture(background_textures[1]);
    background_sprites[2].setTexture(background_textures[2]);
    background_sprites[3].setTexture(background_textures[3]);

}

void Game::renderMap()
{
    m_window.draw(background_sprites[0]);
    m_window.draw(background_sprites[1]);
    m_window.draw(background_sprites[2]);
    m_window.draw(background_sprites[3]);
}

constexpr int height = 10;
constexpr int width = 10;

void Game::runGame(int)
{
    Player p;
    while (m_window.isOpen() && m_open)
    {
        sf::Event event{};
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:

            	break;
                
            case sf::Event::Closed:
                m_window.close();
                break;
            }
        }
        p.update();

        m_window.clear();
        m_window.draw(p);
        m_window.display();
    }
}

void Game::erstelleGame(sf::RenderWindow& i_window) {
    if (!s_game) 
        s_game = new Game(i_window);
}

Game* Game::get_game()
{ return s_game; }

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

