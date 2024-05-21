#pragma once
#include <vector>
#include "enemy/Enemy.h"
#include "Projektil.h"

class EnemyManager
{
	std::vector<std::shared_ptr<Enemy>> m_enemys;
	std::vector<sf::Texture> m_textures; //Enemy Texturen

	inline static bool s_player_moving = false;
	inline static bool s_tower_update = false;
	inline static bool s_walls_update = false;
	std::vector<std::vector<int>> enemys_per_cell;

	inline static EnemyManager* s_instance;
	inline static long long s_enemies_killed = 0;
	inline static long long s_highscore = 0;


	EnemyManager();
public:

	static long long get_highscore();

	static long long get_enemies_killed();

	static EnemyManager* get_instance();

	static void delete_instance();

	static void set_player_moving(const bool i_moving);

	static void set_updated_tower(const bool i_tower_update);

	static void set_walls_update(const bool i_walls_update);

	[[nodiscard]] static bool should_update();

	[[nodiscard]] static bool is_tower_updated();

	[[nodiscard]] static bool is_player_moving();

	[[nodiscard]] static bool is_walls_update();
	void update(float deltatime);

	[[nodiscard]] glm::vec2 enemypos(double radius, glm::vec2 tower_position) const;
	void add_enemy();
	void add_enemy(glm::ivec3 pos, Utils::Priority);
	void add_enemy(glm::ivec3 pos, Utils::Priority priority, int enemy_type);
	[[nodiscard]] std::vector<std::shared_ptr<Enemy>>& get_enemies() { return m_enemys; }
	int naive_enemy_killer();

	void draw(sf::RenderTarget& i_window) const;

};

