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

bool was_empty = true;
thread_local int curr_frame = 0;
void Enemymanager::update()
{
	curr_frame++;
	std::for_each(std::execution::par,m_enemys.begin(), m_enemys.end(), [this](std::shared_ptr<Enemy>& e)
	{
	//std::shared_ptr<Enemy> e = m_enemys[0];
			if (e->hp <= 0)
			{
				e->die();
				e.reset();
				return;
			}
			if (e->m_movements.empty() == true)
			{
			
				was_empty = false;
				glm::vec3 player = Utils::Pathfinding::get_instance()->find_nearest(e->get_pos(), Utils::Priority::player);
				player.x /= 135 / 5;
				player.y /= 135 / 5;
			
				player = round(player);
				glm::vec3 e_pos = e->get_pos();
				e_pos.x /= 135 / 5;
				e_pos.y /= 135 / 5;
				e_pos = round(e_pos);
				e->m_movements = Utils::Pathfinding::get_instance()->find_path
				(
					player, e_pos
				);
			}
			e->m_sprite.setTexture(this->textures[0]); // wird so angepasst, dass es per rotation sich verändert
			if (curr_frame % 6 == 0) {
				for (int i = 0; i < 1; i++)
				{
					if (e->m_movements.empty() == false)
					{
						glm::vec3 temp = e->m_movements[e->m_movements.size() - 1];
						temp.x *= 135/5;
						temp.y *= 135/5;
						e->set_pos(temp);
						e->m_sprite.setPosition(temp.x, temp.y);
						e->m_movements.pop_back();
					}
				}
				curr_frame = 0;
			}

	}
	);


	//for (std::vector<std::shared_ptr<Enemy>>::iterator it = m_enemys.begin(); it != m_enemys.end();)
	//{
	//	if (*it == nullptr)
	//	{
	//		it = m_enemys.erase(it);
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}
}
