#pragma once
#include <vector>
#include "Enemy.h"
class Enemymanager
{
	std::vector<std::shared_ptr<Enemy>> m_enemys;
	std::vector<sf::Texture> textures;

public:
	Enemymanager();
	void update(float deltatime);

	void add_enemy();
	std::vector<std::shared_ptr<Enemy>>& get_enemies() { return m_enemys; }

	void draw(sf::RenderWindow& i_window)
	{
		for (auto m : m_enemys)
		{
			i_window.draw(*m);
		}
	}
};

