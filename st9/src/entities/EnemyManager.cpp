#include "EnemyManager.h"
#include <execution>
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
	enemys_per_cell = std::vector( map[0].size(),
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



	std::for_each(std::execution::par, m_enemys.begin(), m_enemys.end(), [this, &deltatime](std::shared_ptr<Enemy>& e)
	{
			{
				if (e == nullptr)
					return;
				if (e->m_hp <= 0)
				{
					e->die();
					e.reset();
					return;
				}
			}
			if (e->m_movements.empty() == true || should_update())
			{

				const glm::vec3 e_pos = e->m_pos;

				e->m_movements = Utils::Pathfinding::get_instance()->find_path
				(
					e_pos, e->get_priority()
				);
				e->prev_size = e->m_movements.size();
			}
			e->m_sprite.setTexture(this->m_textures[0]); // wird irgendwann so angepasst, dass es per rotation sich verändert
			for (int i = 0; i < 300 * deltatime; i++)
			{
				if (e->m_movements.empty() == false)
				{
					const glm::vec3 temp = e->m_movements.back();
					/*temp.x *= 135;
					temp.y *= 135;*/
					e->m_pos = temp;
					e->m_sprite.setPosition(temp.x, temp.y);
					e->m_movements.pop_back();
				}
			}
			const glm::ivec3 temp_pos = round(e->m_pos / CellSize);
			if(Utils::Pathfinding::get_instance()->is_valid(temp_pos))
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
	constexpr float epsilon = 1e-6f;

	auto comp = [](const std::shared_ptr<Enemy>& e1, const std::shared_ptr<Enemy>& e2)
	{
		return Utils::vec3_almost_equal(e1->m_pos, e2->m_pos, epsilon);
	};

	std::ranges::sort(m_enemys, comp);

}

glm::vec2 EnemyManager::enemypos(const double radius, const glm::vec2 tower_position) const
{
	glm::vec2 nearest (-1);

	const glm::vec2 tower_cell_position = round(tower_position / 135.0f) ;

	const int check_size_x = static_cast<int>(radius);
	const int check_size_y = static_cast<int>(radius);

	for (int x = static_cast<int>(tower_cell_position.x) - check_size_x; x < static_cast<int>(tower_cell_position.x) + check_size_x; x++)
	{
		for (int y = static_cast<int>(tower_cell_position.y) - check_size_y; y < static_cast<int>(tower_cell_position.y) + check_size_y; y++)
		{
			if (Utils::is_valid({ x,y,0.0f }) && enemys_per_cell[y][x] > 0)
			{
				const glm::vec2 distance_new_point_to_tower = abs(glm::vec2{ x,y } - tower_position);
				const glm::vec2 distance_nearest_to_tower = abs(nearest - tower_position);

				if((distance_new_point_to_tower.x+distance_new_point_to_tower.y < distance_nearest_to_tower.x+ distance_nearest_to_tower.y || nearest == glm::vec2{-1.0f,-1.0f}) && distance_new_point_to_tower.x + distance_new_point_to_tower.y < radius)
				{
					nearest = { x * CellWidth,y * CellHeight };
				}
			}
		}
	}


	return nearest;
}

void EnemyManager::add_enemy()
{
	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys.back()->m_priority = static_cast<Utils::Priority>(Utils::Random::UInt(0, 2));
	LOG_TRACE("priority: {}", static_cast<int>(m_enemys.back()->m_priority));
	m_enemys.back()->m_id = 0;
}
void EnemyManager::draw(sf::RenderTarget& i_window) const
{
	glm::vec3 prev_pos(-1);
	for (const auto& m : m_enemys)
	{
		if (!Utils::vec3_almost_equal(prev_pos, m->m_pos, 1e-6f))
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
			bool collision = projectile_max.x > enemy_min.x &&
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
