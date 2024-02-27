#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class MainBuilding
{
	int m_hp;
	int m_pos_x;
	int m_pos_y;
	sf::Sprite m_sprite;
	sf::Texture m_texture;


	public:
		MainBuilding();
		void MainSprite(sf::RenderWindow&);
		

};

