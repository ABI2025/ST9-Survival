#pragma once
#include <SFML/Graphics.hpp>


class Tower
{
	int m_ressourcen;
	double m_hp;
	int m_damage;
	sf::Vector2<float> m_pos;

public:
	Tower();
	~Tower();
	void drawtower(sf::RenderWindow&);
	virtual void fire(){} //warten auf hinzufügen von projectile klasse


};

