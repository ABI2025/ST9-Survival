#pragma once
#include <vector>
#include "Enemy.h"
class Enemymanager
{
	std::vector<std::shared_ptr<Enemy>> m_enemys;
	std::vector<sf::Texture> textures;

public:
	Enemymanager();
	void update();

	void draw(sf::RenderWindow& i_window)
	{
		for (auto m : m_enemys)
		{
			i_window.draw(*m);
		}
	}
};

