#include "Enemymanager.h"
#include <execution>

Enemymanager::Enemymanager()
{
	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys[0]->id = 0;

	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys[1]->id = 0;

	m_enemys.push_back(std::make_shared<Enemy>());
	m_enemys[2]->id = 0;

	textures.resize(1);
	textures[0].loadFromFile("resources/charakter_R.png");
}

void Enemymanager::update()
{
	std::for_each(std::execution::par,m_enemys.begin(), m_enemys.end(), [this](std::shared_ptr<Enemy>& e)
	{
			if (e->hp <= 0)
			{
				e->die();
				e.reset();
				return;
			}
			if (e->m_movements.empty() == true)
			{
				e->m_movements = Utils::Pathfinding::get_instance()->find_path(e->get_pos(),
					Utils::Pathfinding::get_instance()->find_nearest(e->get_pos(), Utils::Priority::player));
			}
			e->m_sprite.setTexture(this->textures[e->id]);
			e->set_pos(e->m_movements[e->m_movements.size()-1]);
			e->m_sprite.setPosition(e->m_movements[e->m_movements.size() - 1].x, e->m_movements[e->m_movements.size() - 1].y);
			e->m_movements.pop_back();
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
}
