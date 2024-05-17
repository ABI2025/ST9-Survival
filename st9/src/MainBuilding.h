#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class MainBuilding
{
	int m_hp;
	float m_pos_x;
	float m_pos_y;
	sf::Sprite m_sprite;
	sf::Texture m_texture;


public:
	MainBuilding();
	void main_sprite(sf::RenderTarget&) const;


};

