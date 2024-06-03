#include "MainBuilding.h"

#include "Game.h"
#include "Optionen.h"


MainBuilding::MainBuilding() : m_pos_x(135 * 20), m_pos_y(135 * 10)
{
	m_pos = { m_pos_x,m_pos_y,0.f };
	m_texture.loadFromFile("Resources/images/Spawn.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(135.f /2.f, 135.f);
	m_sprite.setPosition(m_pos_x +135.f/2.f, m_pos_y+135.f);
	m_health = 5000;

}

void MainBuilding::update(float deltatime)
{
	if (Optionen::get_instance()->get_should_rotate())
		m_sprite.rotate(36 * deltatime);
	else
		m_sprite.setRotation(0);
}


void MainBuilding::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

