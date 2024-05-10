#include "MainBuilding.h"


MainBuilding::MainBuilding(): m_hp(0), m_pos_x(135*20), m_pos_y(135*10)
{
	m_texture.loadFromFile("Resources/images/Spawn.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos_x, m_pos_y);
}

void MainBuilding::main_sprite(sf::RenderTarget& target) const
{
	target.draw(m_sprite);
}

