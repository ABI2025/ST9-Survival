#pragma once
#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"

class Tower
{
	int m_ressourcen;
	double m_hp;
	int m_damage;
	glm::ivec3 m_pos;

public:
	Tower();
	~Tower();
	void drawtower(sf::RenderWindow&);
	virtual void fire(){} //warten auf hinzufügen von projectile klasse


};

