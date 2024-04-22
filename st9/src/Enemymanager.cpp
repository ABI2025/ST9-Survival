#include "EnemyManager.h"
#include <execution>
#include "Utils/Utils.h"

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

	textures.resize(1);
	textures[0].loadFromFile("resources/charakter_R.png");
	Utils::Pathfinding::get_instance()->calculate_paths();

}

int curr_frame = 0;
constexpr float time_per_frame = 1 / 60.0f;
float con_dt = 0.0f;
thread_local size_t  prev_size = 0;
void EnemyManager::update(float deltatime)
{
	if(s_player_moving)
		Utils::Pathfinding::get_instance()->calculate_paths();
	con_dt += deltatime;
	curr_frame++;
	std::for_each(std::execution::par,m_enemys.begin(), m_enemys.end(), [this,&deltatime](std::shared_ptr<Enemy>& e)
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
			if (e->m_movements.empty() == true || (s_player_moving))
			{
				//e->m_hp--;
				/*player.x /= 135;
				player.y /= 135;*/
			
				glm::vec3 e_pos = e->m_pos;
				/*e_pos.x /= 135;
				e_pos.y /= 135;*/
				e->m_movements = Utils::Pathfinding::get_instance()->find_path
				(
					e_pos, Utils::Priority::nothing
				);
				e->prev_size = e->m_movements.size();
			}
			e->m_sprite.setTexture(this->textures[0]); // wird irgendwann so angepasst, dass es per rotation sich verändert
			//if (curr_frame % 2 == 0) {
				for (int i = 0; i < 300 * deltatime; i++)
				{
					if (e->m_movements.empty() == false)
					{
						glm::vec3 temp = e->m_movements[e->m_movements.size() - 1];
						/*temp.x *= 135;
						temp.y *= 135;*/
						e->m_pos = temp;
						e->m_sprite.setPosition(temp.x, temp.y);
						e->m_movements.pop_back();
					}
				}
			//}

	}
	);
	
	for (std::vector<std::shared_ptr<Enemy>>::iterator it = m_enemys.begin(); it != m_enemys.end();)
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
	constexpr float epsilon = 1e-6;

	auto comp = [](std::shared_ptr<Enemy>& e1, std::shared_ptr<Enemy>& e2)
		{
			return Utils::vec3_almost_equal(e1->m_pos, e2->m_pos,epsilon);
		};

	std::ranges::sort(m_enemys, comp);
	if (con_dt > 1)
		con_dt = 0;
	if (curr_frame == 1200)
	{
		curr_frame = 0;
	}
}

void EnemyManager::add_enemy()
{
	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys.back()->m_id = 0;
}
void EnemyManager::draw(sf::RenderWindow& i_window) const
{
	glm::vec3 prev_pos (-1);
	for (const auto& m : m_enemys)
	{
		if (!Utils::vec3_almost_equal(prev_pos, m->m_pos, 1e-6))
		{
			i_window.draw(*m);
		}
		prev_pos = m->m_pos;
	}
}
