#pragma once
#include <vector>
#include "enemy/Enemy.h"
#include "Projektil.h"

class EnemyManager
{
	std::vector<std::shared_ptr<Enemy>> m_enemys;
	std::vector<sf::Texture> m_textures;
	
	inline static bool s_player_moving = false;
	inline static bool s_tower_update = false;
	std::vector<std::vector<int>> enemys_per_cell;
public:
	static void set_player_moving(const bool i_moving)
	{ s_player_moving = i_moving;}
	static void set_updated_tower(const bool i_tower_update)
	{ s_tower_update = i_tower_update;}
	[[nodiscard]] static bool should_update()
	{ return s_tower_update || s_player_moving; }
	EnemyManager();
	void update(float deltatime);

	[[nodiscard]] glm::vec2 enemypos(double radius, glm::vec2 tower_position) const;
	void add_enemy();
	[[nodiscard]] std::vector<std::shared_ptr<Enemy>>& get_enemies() { return m_enemys; }
	int naive_enemy_killer();

	void draw(sf::RenderTarget& i_window) const;

};

