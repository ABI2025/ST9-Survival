// ReSharper disable CppTooWideScopeInitStatement
#include "EnemyManager.h"
#include <execution>
#include "Wave.h"
#include "Game.h"
#include "Utils/Utils.h"

constexpr float CellHeight = 135.0f;
constexpr float CellWidth = 135.0f;
constexpr float CellSize = 135.0f;

EnemyManager::EnemyManager()
{
	m_textures.resize(5);
	m_textures[0].loadFromFile("resources/images/gegner1-1.png");
	m_textures[1].loadFromFile("resources/images/Roter_gegner1-1.png");
	m_textures[2].loadFromFile("resources/images/Blauer_gegner1-1.png");
	m_textures[3].loadFromFile("resources/images/Gold_gegner1-1.png");
	m_textures[4].loadFromFile("resources/images/Schwarzer_gegner1-1.png");

	const auto& map = Utils::Pathfinding::get_instance()->get_map();
	enemys_per_cell = std::vector(map[0].size(),
		std::vector(map[0][0].size(), 0));
	std::ifstream fin("highscore.txt");
	if(fin.is_open())
	{
		fin >> s_highscore;
	}
	else
	{
		std::ofstream fout;
		fout.open("highscore.txt");
		fout.close();
	}
}

long long EnemyManager::get_highscore()
{
	return s_highscore;
}

long long EnemyManager::get_enemies_killed()
{
	return s_enemies_killed;
}

EnemyManager* EnemyManager::get_instance()
{
	if (!s_instance)
		s_instance = new EnemyManager;
	return s_instance;
}

void EnemyManager::delete_instance()
{
	std::fstream fstream("highscore.txt");
	if(s_enemies_killed > s_highscore)
		fstream << s_enemies_killed;
	delete s_instance;
	s_instance = nullptr;
}

void EnemyManager::set_player_moving(const bool i_moving)
{
	s_player_moving = i_moving;
}

void EnemyManager::set_updated_tower(const bool i_tower_update)
{
	s_tower_update = i_tower_update;
}

void EnemyManager::set_walls_update(const bool i_walls_update)
{
	s_walls_update = i_walls_update;
}

bool EnemyManager::should_update()
{
	return s_tower_update || s_player_moving || s_walls_update;
}

bool EnemyManager::is_tower_updated()
{
	return s_tower_update;
}

bool EnemyManager::is_player_moving()
{
	return s_player_moving;
}

bool EnemyManager::is_walls_update()
{
	return s_walls_update;
}

void EnemyManager::update(float deltatime)
{
	for (std::vector<int>& vector : enemys_per_cell)
	{
		for (int& i : vector)
		{
			i = 0;
		}
	}
	auto& tower = Game::get_game()->getEntityMap();
	std::for_each(std::execution::par, m_enemys.begin(), m_enemys.end(), [this, &deltatime, &tower](std::shared_ptr<Enemy>& e)
		{
			{
				if (e == nullptr)
					return;
				if (e->m_health <= 0 || e->currently_dying)
				{
					e->die();
					if (e->can_be_removed)
					{
						Game::get_game()->add_geld(10); // müssten wir gebalanced gehabt haben
						e.reset();
						s_enemies_killed++;
					}
					return;
				}
			}

			if (!should_update())
			{
				const glm::ivec3 temp = e->m_pos;
				const glm::ivec3 cell_pos = round(e->m_pos / CellSize);
				if (Utils::Pathfinding::get_instance()->is_valid(cell_pos))
				{
					if (tower[0][cell_pos.y][cell_pos.x] != nullptr)
					{
						

						e->attack();

						enemys_per_cell[cell_pos.y][cell_pos.x]++;

						e->m_pos = temp;
						e->m_hitbox = e->m_pos + glm::vec3{ 135,135,0 };
						e->m_sprite.setPosition(e->m_pos.x, e->m_pos.y);
						return;
					}

				}
			}


			if (e->m_movements.empty() == true || should_update())
			{
				e->m_movements = Utils::Pathfinding::get_instance()->find_path
				(
					e->m_pos, e->m_priority
				);
				e->prev_size = e->m_movements.size();
			}

			//e->m_sprite.setTexture(this->m_textures[0]); // wird irgendwann so angepasst, dass es per rotation sich verändert

			for (int i = 0; i < 300 * deltatime * e->m_speed; i++)
			{
				if (e->m_movements.empty() == false)
				{
					const glm::ivec3 temp = e->m_movements.back();
					/*temp.x *= 135;
					temp.y *= 135;*/
					const glm::ivec3 cell_pos = round(e->m_pos / CellSize);
					if (Utils::Pathfinding::get_instance()->is_valid(cell_pos) && tower[0][cell_pos.y][cell_pos.x] != nullptr)
					{

						enemys_per_cell[cell_pos.y][cell_pos.x]++;
						e->m_hitbox = e->m_pos + glm::vec3{ 135,135,0 };
						e->attack();
						e->m_sprite.setPosition(e->m_pos.x, e->m_pos.y);
						tower[0][cell_pos.y][cell_pos.x]->take_damage(e->m_damage);
						return;
					}


					e->m_pos = temp;
					e->m_sprite.setPosition(e->m_pos.x, e->m_pos.y);
					e->m_movements.pop_back();

				}
			}
			const glm::ivec3 temp_pos = round(e->m_pos / CellSize);

			if (Utils::Pathfinding::get_instance()->is_valid(temp_pos))
			{
				enemys_per_cell[temp_pos.y][temp_pos.x]++;
			}

			e->m_hitbox = e->m_pos + glm::vec3{ 135,135,0 };
		}
	);

	for (auto it = m_enemys.begin(); it != m_enemys.end();)
	{
		if (*it == nullptr)
		{
			it = m_enemys.erase(it);
		}
		else
		{
			++it;
		}
	}



	for (int i = 0; i < enemys_per_cell.size(); ++i)
	{
		for (int j = 0; j < enemys_per_cell[i].size(); ++j)
		{
			if (tower[0][i][j] != nullptr && enemys_per_cell[i][j] > 0)
			{
				tower[0][i][j]->take_damage(enemys_per_cell[i][j] * 0.1);
			}
			
		}
	}



	constexpr float epsilon = 1e-6f;

	auto comp = [](const std::shared_ptr<Enemy>& e1, const std::shared_ptr<Enemy>& e2)
		{
			return Utils::vec3_almost_equal(e1->m_pos, e2->m_pos, epsilon);
		};

	std::ranges::sort(m_enemys, comp);

}

glm::vec2 EnemyManager::enemypos(const double radius, const glm::vec2 tower_position) const
{
	glm::vec2 nearest(-1);
	glm::ivec2 nearest_cell_position(-1);

	const glm::ivec2 tower_cell_position = round(tower_position / 135.0f);

	const int check_size_x = static_cast<int>(radius);
	const int check_size_y = static_cast<int>(radius);
	//LOG_INFO("tower_cell_position x: {}  tower_cell_position y: {}", tower_cell_position.x, tower_cell_position.y);

	for (int x = static_cast<int>(tower_cell_position.x) - check_size_x; x < static_cast<int>(tower_cell_position.x) + check_size_x; x++)
	{
		for (int y = static_cast<int>(tower_cell_position.y) - check_size_y; y < static_cast<int>(tower_cell_position.y) + check_size_y; y++)
		{
			if (Utils::is_valid({ x,y,0.0f }) && enemys_per_cell[y][x] > 0)
			{
				const glm::ivec2 distance_new_point_to_tower = (glm::ivec2{ x,y } - tower_cell_position);
				const glm::ivec2 distance_nearest_to_tower = (nearest_cell_position - tower_cell_position);
#ifndef euclid
				const int manhatten_distance_new_point_to_tower = abs(distance_new_point_to_tower.x) + abs(distance_new_point_to_tower.y);
				const int manhatten_distance_nearest_to_tower = abs(distance_nearest_to_tower.x) + abs(distance_nearest_to_tower.y);
				if ((manhatten_distance_new_point_to_tower < manhatten_distance_nearest_to_tower
					|| nearest == glm::vec2{ -1.0f,-1.0f })
					&& manhatten_distance_new_point_to_tower <= radius)
				{
					nearest = { x * CellWidth,y * CellHeight };
					nearest_cell_position = { x,y };
				}
#else
				const int euclidean_distance_new_point_to_tower = sqrt(pow(distance_new_point_to_tower.x, 2) + pow(distance_new_point_to_tower.y, 2));
				const int euclidean_distance_nearest_to_tower = sqrt(pow(distance_nearest_to_tower.x, 2) + pow(distance_nearest_to_tower.y, 2));
				if ((euclidean_distance_new_point_to_tower < euclidean_distance_nearest_to_tower
					|| nearest == glm::vec2{ -1.0f,-1.0f })
					&& euclidean_distance_new_point_to_tower <= radius)
				{
					nearest = { x * CellWidth,y * CellHeight };
					nearest_cell_position = { x,y };
				}
#endif
			}
		}
	}


	return nearest;
}

void EnemyManager::add_enemy()
{
	const std::shared_ptr spawned_enemy = { std::make_shared<Enemy>() };
	m_enemys.push_back(spawned_enemy);

	spawned_enemy->m_priority = static_cast<Utils::Priority>(Utils::Random::UInt(0, 2));
	LOG_TRACE("priority: {}", static_cast<int>(spawned_enemy->m_priority));
	spawned_enemy->m_id = 0;
}

void EnemyManager::add_enemy(glm::ivec3 pos, Utils::Priority priority) //veraltet nutzung meiden
{
	const std::shared_ptr spawned_enemy = { std::make_shared<Enemy>() };
	m_enemys.push_back(spawned_enemy);
	spawned_enemy->m_priority = priority;
	spawned_enemy->m_pos = pos;
	spawned_enemy->m_id = 0;
}
void EnemyManager::add_enemy(glm::ivec3 pos, Utils::Priority priority , int i_enemy_type)
{
	const std::shared_ptr spawned_enemy = { std::make_shared<Enemy>() };
	m_enemys.push_back(spawned_enemy);
	spawned_enemy->m_priority = priority;
	spawned_enemy->m_pos = pos;
	spawned_enemy->m_id = 0;
	spawned_enemy->m_enemy_type = static_cast<enemy_type>(i_enemy_type);
	spawned_enemy->m_sprite.setTexture(m_textures[i_enemy_type]);
	switch(i_enemy_type){
	case 1: // Roter Gegner
		spawned_enemy->m_health = 1.4; // ist default
		spawned_enemy->m_damage = 5; // 0.1 ist default
		spawned_enemy->m_speed = 2; // 1 ist default
		break;
	case 2: // Blauer Gegner
		spawned_enemy->m_health = 8;
		spawned_enemy->m_damage = 0.5;
		break;
	case 3: //gold
		spawned_enemy->m_speed = 1.3 + Wave::wave_counter * 0.02;
		spawned_enemy->m_damage = 1 + Wave::wave_counter * 0.08;
		spawned_enemy->m_health = 8 + Wave::wave_counter;
		break;
	case 4: //schwarz
		spawned_enemy->m_speed = 0.5;
		spawned_enemy->m_damage = 0.5;
		spawned_enemy->m_health = 20;
		break;
	}
}
void EnemyManager::draw(sf::RenderTarget& i_window) const
{
	glm::vec3 prev_pos(-1);
	for (const auto& m : m_enemys)
	{
		if (!Utils::vec3_almost_equal(prev_pos, m->m_pos, 1e-6f) || m->currently_dying)
		{
			i_window.draw(*m);
		}
		prev_pos = m->m_pos;
	}
}
/*
int EnemyManager::naiveEnemyKiller(Projectile * projectile) {
	int hitCount = 0;
	sf::FloatRect projectileBounds = projectile->get_sprite().getGlobalBounds();

	for (auto& enemy : m_enemys) {
		if (enemy && enemy->isAlive()) {
			sf::FloatRect enemyBounds = enemy->get_sprite().getGlobalBounds();

			if (projectileBounds.intersects(enemyBounds)) {
				enemy->die();
				hitCount++;
			}
		}
	}

	return hitCount;
}
*/
//#include <glm/gtx/string_cast.hpp> // For glm::to_string

int EnemyManager::naive_enemy_killer() {
	int hit_count = 0;
	std::vector<Projectile*> to_remove_projectiles;

	for (Projectile* projectile : Projectile::get_projectiles()) {
		if (projectile->get_penetration() <= 0) {
			to_remove_projectiles.push_back(projectile);
			continue;
		}

		glm::vec3 projectile_pos = projectile->get_pos();
		glm::vec3 projectile_hitbox = projectile->get_hit_box(); // Using the new get_hitBox method
		glm::vec3 projectile_min = projectile_pos; // warum????
		glm::vec3 projectile_max = projectile_hitbox;

		for (auto& enemy : m_enemys) {
			if (!enemy->is_alive()) {
				continue;
			}

			glm::vec3 enemy_pos = enemy->get_pos();
			glm::vec3 enemy_hitbox = enemy->get_hit_box(); // Using the new get_hitBox method
			glm::vec3 enemy_min = enemy_pos;
			glm::vec3 enemy_max = enemy_hitbox; // btw chat gpt ist richtig inkompetent

			// Check if hitboxes intersect
			const bool collision = projectile_max.x > enemy_min.x &&
				projectile_min.x < enemy_max.x &&
				projectile_max.y > enemy_min.y &&
				projectile_min.y < enemy_max.y;

			if (collision) {
				enemy->take_damage(projectile->get_damage());
				hit_count++;

				projectile->decrease_penetration(1);
				if (projectile->get_penetration() <= 0) {
					to_remove_projectiles.push_back(projectile);
					break;
				}
			}
		}
	}

	// Clean up projectiles
	for (Projectile* projectile : to_remove_projectiles)
	{
		Projectile::remove_projectile(projectile);
	}

	return hit_count;
}
