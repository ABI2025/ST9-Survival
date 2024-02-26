#include "MainBuilding.h"


MainBuilding::MainBuilding()
{
	m_texture.loadFromFile("Resources/Spawn.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);
}

void MainBuilding::MainSprite(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

