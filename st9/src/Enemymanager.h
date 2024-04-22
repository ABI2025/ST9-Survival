#pragma once
#include <vector>
#include "Enemy.h"
#include "Projektil.h"
class EnemyManager
{
	std::vector<std::shared_ptr<Enemy>> m_enemys;
	std::vector<sf::Texture> textures;
	inline static bool s_player_moving = false;
public:
	static void set_player_moving(bool i_moving) { s_player_moving = i_moving; }
	EnemyManager();
	void update(float deltatime);

	void add_enemy();
	std::vector<std::shared_ptr<Enemy>>& get_enemies() { return m_enemys; }
	int naiveEnemyKiller();
	void draw(sf::RenderWindow& i_window) const;
};

