#pragma once
#include <vector>
#include "Enemy.h"
class EnemyManager
{
	std::vector<std::shared_ptr<Enemy>> m_enemys;
	std::vector<sf::Texture> textures;
	
	inline static bool s_player_moving = false;
public:
	static void set_player_moving(bool i_moving) { s_player_moving = i_moving; }
	EnemyManager();
	void update(float deltatime);
	glm::vec2 enemypos(double rad,glm::vec2 pos)
	{
		glm::vec2 nearst (-1);
		double dist = DBL_MAX;
		for(auto enemy : m_enemys)
		{
			double temp = sqrt(pow(pos.x - enemy->m_pos.x, 2) + pow(pos.y - enemy->m_pos.y, 2));
			if(temp < dist)
			{
				dist = temp;
				nearst = { enemy->m_pos.x,enemy->m_pos.y };
			}
		}
		if (dist > rad) 
			return { -1.0f,-1.0f };

		return nearst;
	};
	void add_enemy();
	std::vector<std::shared_ptr<Enemy>>& get_enemies() { return m_enemys; }

	void draw(sf::RenderWindow& i_window) const;

};

