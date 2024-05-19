#include "MainBuilding.h"

#include "Game.h"


MainBuilding::MainBuilding() : m_pos_x(135 * 20), m_pos_y(135 * 10)
{
	m_pos = { m_pos_x,m_pos_y,0.f };
	m_texture.loadFromFile("Resources/images/Spawn.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos_x, m_pos_y);
	m_health = 50000000;

}



void MainBuilding::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

