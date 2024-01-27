#include "Enemymanager.h"
#include <execution>

Enemymanager::Enemymanager()
{
	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys[0]->id = 0;

	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys[1]->id = 0;
	m_enemys[1]->m_pos = {135,135,0};


	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys[2]->id = 0;
	m_enemys[2]->m_pos = { 135*3,135*3,0 };

	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys[3]->id = 0;

	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys[4]->id = 0;
	m_enemys[4]->m_pos = {135,135,0};


	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys[5]->id = 0;
	m_enemys[5]->m_pos = { 135*3,135*3,0 };

	textures.resize(1);
	textures[0].loadFromFile("resources/charakter_R.png");
}

int curr_frame = 0;
constexpr float time_per_frame = 1 / 60.0f;
float con_dt = 0.0f;
void Enemymanager::update(float deltatime)
{
	con_dt += deltatime;
	curr_frame++;
	std::mutex mutex;
	std::for_each(std::execution::par,m_enemys.begin(), m_enemys.end(), [this,&mutex,&deltatime](std::shared_ptr<Enemy>& e)
	{
		{
			if (e == nullptr)
				return;
			if (e->hp <= 0)
			{
				e->die();
				e.reset();
				return;
			}

		}
			if (e->m_movements.empty() == true || curr_frame % 60 == 0)
			{
				//e->hp--;
				glm::vec3 player = Utils::Pathfinding::get_instance()->find_nearest(e->get_pos(), Utils::Priority::player);
				player.x /= 135;
				player.y /= 135;
			
				glm::vec3 e_pos = e->get_pos();
				e_pos.x /= 135;
				e_pos.y /= 135;
				e->m_movements = Utils::Pathfinding::get_instance()->find_path
				(
					player, e_pos
				);
			}
			e->m_sprite.setTexture(this->textures[0]); // wird irgendwann so angepasst, dass es per rotation sich verändert
			if (curr_frame % 2 == 0) {
				for (int i = 0; i < 300 * deltatime; i++)
				{
					if (e->m_movements.empty() == false)
					{
						glm::vec3 temp = e->m_movements[e->m_movements.size() - 1];
						/*temp.x *= 135;
						temp.y *= 135;*/
						e->set_pos(temp);
						e->m_sprite.setPosition(temp.x, temp.y);
						e->m_movements.pop_back();
					}
				}
			}

	}
	);
	if (con_dt > 1)
		con_dt = 0;
	if (curr_frame == 1200)
	{
		curr_frame = 0;
	}
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
}

void Enemymanager::add_enemy()
{
	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys.back()->id = 0;
}
