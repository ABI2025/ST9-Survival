#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <SFML/Graphics.hpp>

std::vector<std::vector<std::array<uint8_t, 2>>> erstelleMap();

class Game
{
public:
	void renderMap();
	static void erstelleGame(sf::RenderWindow&);
	static Game* get_game();

	void setMap(Utils::Cell& , int , int , int ); // Cell x,y,z

	std::vector<std::vector<std::vector<Utils::Cell>>>& get_map();

	void runGame(int);

	Game(Game&) = delete;
private:
	inline static Game* s_game;
	Game(sf::RenderWindow&);
	sf::RenderWindow& m_window; 
	std::vector<std::vector<std::vector<Utils::Cell>>> m_map;
	std::vector<sf::Sprite> background_sprites;
	std::vector<sf::Texture> background_textures;
	bool m_open = true;
};
