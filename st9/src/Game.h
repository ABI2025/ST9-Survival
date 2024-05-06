#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <SFML/Graphics.hpp>

#include "Sounds.h"

std::vector<std::vector<std::array<uint8_t, 2>>> erstelle_map();

class Game
{
public:
	void render_map(glm::vec3 player_pos);
	void render_tower() const;
	static void erstelle_game(sf::RenderWindow&);
	static Game* get_game();

	void set_map(const Utils::Cell& , int x , int y, int z); // Cell x,y,z

	std::vector<std::vector<std::vector<Utils::Cell>>>& get_map();

	void run_game(int);

	Game(Game&) = delete;
private:
	inline static Game* s_game;
	explicit Game(sf::RenderWindow&);
	sf::RenderWindow& m_window; 
	std::vector<std::vector<std::vector<Utils::Cell>>> m_map;
	std::vector<sf::Sprite> m_background_sprites;
	std::vector<sf::Texture> m_background_textures;
	std::vector<sf::Texture> m_building_textures;
	std::vector<std::vector<std::array<uint8_t, 2>>> m_tiles;
	Sounds m_sounds;

	bool m_open = true;
};
