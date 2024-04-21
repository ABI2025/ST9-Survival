#pragma once
#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"
class Player;
class healthbar
{
private:
	int m_health;
public:
	healthbar();
	~healthbar();
	void regeneration(int);

	int get_health();

	void damage_input(int);
	void draw_healthbar(sf::RenderWindow&, Player&);

};

