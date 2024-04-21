#include "Tower.h"

Tower::Tower()
{
	m_ressourcen = 0;
	m_hp = 0;
	m_damage = 0;
	//m_pos = {0.0f,0.0f};
}
Tower::~Tower()
{
	
}

void Tower::drawtower(sf::RenderWindow& window )
{
	sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.0f));
	rectangle.setFillColor(sf::Color::Red);
	//rectangle.setPosition(m_pos);
	
	window.draw(rectangle);
	
}


