#pragma once
#include <SFML/Graphics.hpp>

#include "entities/entity/Entity.h"

class MainBuilding: public Entity
{
	float m_pos_x;
	float m_pos_y;
	sf::Texture m_texture;


public:
	MainBuilding();
	void update(float deltatime) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

