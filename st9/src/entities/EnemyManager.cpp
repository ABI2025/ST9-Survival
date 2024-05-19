// ReSharper disable CppTooWideScopeInitStatement
#include "EnemyManager.h"
#include <execution>

#include "Game.h"
#include "Utils/Utils.h"

constexpr float CellHeight = 135.0f;
constexpr float CellWidth = 135.0f;
constexpr float CellSize = 135.0f;

EnemyManager::EnemyManager()
{
	//m_enemys.push_back(std::make_shared<Enemy>());
	//m_enemys[0]->m_id = 0;

	//m_enemys.push_back(std::make_shared<Enemy>());
	//m_enemys[1]->m_id = 0;
	//m_enemys[1]->m_pos = {135,135,0};


	//m_enemys.push_back(std::make_shared<Enemy>());
	//m_enemys[2]->m_id = 0;
	//m_enemys[2]->m_pos = { 135*3,135*3,0 };

	//m_enemys.push_back(std::make_shared<Enemy>());
	//m_enemys[3]->m_id = 0;

	//m_enemys.push_back(std::make_shared<Enemy>());
	//m_enemys[4]->m_id = 0;
	//m_enemys[4]->m_pos = {135,135,0};


	//m_enemys.push_back(std::make_shared<Enemy>());
	//m_enemys[5]->m_id = 0;
	//m_enemys[5]->m_pos = { 135*3,135*3,0 };

	m_textures.resize(1);
	m_textures[0].loadFromFile("resources/images/gegner1-1.png");


	const auto& map = Utils::Pathfinding::get_instance()->get_map();
	enemys_per_cell = std::vector(map[0].size(),
		std::vector(map[0][0].size(), 0));
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
						Game::get_game()->add_geld(10); // müssten wir gebalanced gehabt haben, später
						e.reset();
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
						e->m_sprite.setTexture(this->m_textures[0]);

						e->attack();

						enemys_per_cell[cell_pos.y][cell_pos.x]++;

						e->m_hitbox = e->m_pos + glm::vec3{ 135,135,0 };
						e->m_pos = temp;
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

			e->m_sprite.setTexture(this->m_textures[0]); // wird irgendwann so angepasst, dass es per rotation sich verändert

			for (int i = 0; i < 300 * deltatime; i++)
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

				//LOG_INFO("manhatten_distance_new_point_to_tower {}", manhatten_distance_new_point_to_tower);
				//LOG_INFO("manhatten_distance_nearest_to_tower {}", manhatten_distance_nearest_to_tower);
				//LOG_INFO("x: {} y: {}", x,y);


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

void EnemyManager::add_enemy(glm::ivec3 pos, Utils::Priority priority)
{
	LOG_INFO("pos: x : {} y: {} z: {}", pos.x, pos.y, pos.z);
	LOG_INFO("pos:x: {} y: {} z: {}", pos.x / 135.0f, pos.y / 135.0f, pos.z / 135.0f);
	const std::shared_ptr spawned_enemy = { std::make_shared<Enemy>() };
	m_enemys.push_back(spawned_enemy);
	spawned_enemy->m_priority = priority;
	spawned_enemy->m_pos = pos;
	spawned_enemy->m_id = 0;
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
