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
	~healthbar() = default;
	void regeneration(int);

	[[nodiscard]] int get_health() const;

	[[nodiscard]] bool damage_input(int);
	[[nodiscard]] bool alive() const;
	void draw_healthbar(sf::RenderWindow&, Player&) const;

};

