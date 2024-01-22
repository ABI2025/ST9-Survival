#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <SFML/Graphics.hpp>

std::vector<std::vector<uint8_t[2]>> erstelleMap();

class Game
{
public:
	int renderMap(sf::RenderWindow&);
	static Game* erstelleGame();
	void setMap(Utils::Cell& , int , int , int ); // Cell x,y,z
	std::vector<std::vector<std::vector<Utils::Cell>>>& get_map();
	void runGame(int);
private:
	inline static Game* s_game;
	Game();
	Game(Game&) = delete;
	std::vector<std::vector<std::vector<Utils::Cell>>> m_map;
	std::vector<sf::Sprite> background_sprites;
	std::vector<sf::Texture> background_textures;


	
};
