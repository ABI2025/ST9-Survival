#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <imgui.h>
#include "Camera.h"
#include "imgui-SFML.h"
#include "Player.h"

constexpr int BACKGROUND_HEIGHT = 135;
constexpr int BACKGROUND_WIDTH = 135;

constexpr int height = 10;
constexpr int width = 20;

std::vector<std::vector<std::array<uint8_t, 2>>> erstelleMap()
{
    std::vector<std::vector<std::array<uint8_t, 2>>> KARTE;
    std::array<uint8_t, 2> single_cell = { 0,0 };
    for (int i = 0; i < width; i++)
    {
        std::vector<std::array<uint8_t, 2>> inner_map;
        for (int j = 0; j < height; j++)
        {
            single_cell[0] = Utils::Random::UInt(0, 3);
            inner_map.emplace_back(single_cell);

        }
        KARTE.emplace_back(inner_map);
    }
    return KARTE;
}

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
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            background_sprites[m_tiles[i][j][0]].setPosition(i * BACKGROUND_WIDTH, j * BACKGROUND_HEIGHT);
            m_window.draw(background_sprites[m_tiles[i][j][0]]);
        }
    }


}


void Game::runGame(int)
{
    Player p;
    Camera c(&m_window,&p);
    m_tiles = erstelleMap();
    while (m_window.isOpen() && m_open)
    {
        sf::Event event{};
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Key::Escape)
                    return;
            	break;
                
            case sf::Event::Closed:
                m_window.close();
                break;
            }
        }
        p.update();
        c.move_cam_to_player();
        m_window.clear();
        renderMap();
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

