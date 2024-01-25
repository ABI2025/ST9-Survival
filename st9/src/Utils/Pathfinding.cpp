#include "Pathfinding.h"

#include "../Player.h"

namespace Utils {
	Pathfinding* Pathfinding::s_instance = nullptr;


	void Pathfinding::Init(std::shared_ptr<Player> i_player, std::vector<std::vector<std::vector<Utils::Cell>>>& i_map)
	{
		if(!s_instance)
			s_instance = new Pathfinding(i_player,i_map);
	}

	void Pathfinding::Delete()
	{
		delete s_instance;
		s_instance = nullptr;
	}


	Pathfinding* Pathfinding::get_instance()
	{
		if (!s_instance)
			throw std::exception("Pathfinding::Init muss vor Pathfinding::get_instance() gerufen werden");
		return s_instance;
	}

	glm::vec3 Pathfinding::find_nearest(const glm::vec3& start, Priority i_priority)
	{
		switch (i_priority)
		{
		case Priority::nothing:
			glm::vec3 pos1 = glm::abs(m_player->get_pos() - start);
			glm::vec3 pos2 = glm::abs(glm::vec3{ 1,1,1 } - start);
			glm::vec3 min_dist = 2 ? glm::vec3(1) : glm::vec3(1);


			return min_dist;
			break;
		case Priority::player:
			return m_player->get_pos();
			break;
		case Priority::tower: break;
		}
		return { -1,-1,-1 };
	}

	std::vector<glm::vec3> Pathfinding::find_path(const glm::vec3& dest, const glm::vec3& start)
	{
		return dijkstra(dest, start);
	}


	Pathfinding::Pathfinding(const std::shared_ptr<Player>& i_player, std::vector<std::vector<std::vector<Utils::Cell>>>& i_map ): m_player(i_player), m_map(i_map)
	{
		/*for (int i = 0; i < m_map.size(); i++)
		{
			std::vector<std::vector<cell>> t_vec_vec_c;

			for (int j = 0; j < m_map[i].size(); j++)
			{
				std::vector<cell> t_vec_c;
				for (int k = 0; k < m_map[i][j].size(); k++)
				{
					t_vec_c.push_back({ {k,j,i },DBL_MAX,nullptr });
				}
				t_vec_vec_c.push_back(t_vec_c);
			}
			m_cellmap.push_back(t_vec_vec_c);
		}*/
	}

	Pathfinding::~Pathfinding() = default;

	std::vector<glm::vec3> Pathfinding::dijkstra(const glm::vec3& dest, const glm::vec3& start)
	{




		std::vector<std::vector<std::vector<cell>>> m_cellmap =
			std::vector(m_map.size(),std::vector(m_map[0].size(),
				std::vector(m_map[0][0].size(),
				cell{{0,0,0},DBL_MAX,DBL_MAX,nullptr})));

		std::vector<cell*> q_vector;

		for(int i = 0; i < m_map.size();i++)
		{
			for(int j = 0; j < m_map[i].size();j++)
			{
				for(int k = 0; k < m_map[i][j].size(); k++)
				{
					m_cellmap[i][j][k].pos = { k, j, i };
					const glm::vec3 temp = dest - glm::vec3(k, j, i);
					m_cellmap[i][j][k].h_dist = temp.x+temp.y;
					q_vector.push_back(&m_cellmap[i][j][k]);
						
				}
			}
		}
		m_cellmap[start.z][start.y][start.x].dist = 0;





		auto comp = [](const cell* c1,const cell* c2)->bool
		{
			return (c1->dist+c1->h_dist) > (c2->dist+c2->h_dist);
		};
		int i = 5;
		while (!q_vector.empty())
		{
			std::sort(q_vector.begin(), q_vector.end(), comp);
			cell* u = q_vector.back();
			//LOG_DEBUG("u: addrese:  ; dist: {} ; h_dist: {} ; pos: x:{} y:{} z:{}", u->dist,u->h_dist,u->pos.x,u->pos.y, u->pos.z);
			q_vector.pop_back();
			for(cell* v : get_neighbours(u,q_vector, m_cellmap))
			{
				//if (v->pos.z != 0)
				//	LOG_CRITICAL("somethings fishy");
				//LOG_DEBUG("v: addrese:  ; dist: {} ; h_dist: {} ; pos: x:{} y:{} z:{}", v->dist, v->h_dist, v->pos.x, v->pos.y, v->pos.z);

				const double dist = u->dist + get_dist(u,v);
				if (dist < m_cellmap[v->pos.z][v->pos.y][v->pos.x].dist)
				{
					m_cellmap[v->pos.z][v->pos.y][v->pos.x].dist = dist;
					m_cellmap[v->pos.z][v->pos.y][v->pos.x].parent = &m_cellmap[u->pos.z][u->pos.y][u->pos.x];
				}
			}
			if(m_cellmap[dest.z][dest.y][dest.x].dist != DBL_MAX && m_cellmap[dest.z][dest.y][dest.x].parent != nullptr)
			{
				i--;

			}
			if (i == 0)
				break;
		}

		std::vector<glm::vec3> bewegungsablauf;
		cell* u = &m_cellmap[dest.z][dest.y][dest.x];
		while(u->parent != nullptr)
		{
			bewegungsablauf.push_back(u->pos);
			u = u->parent;
		}
		//std::ranges::reverse(bewegungsablauf);
		return bewegungsablauf;
	}




	bool Pathfinding::is_valid(glm::vec3 pos) const
	{
		if (!(pos.z < m_map.size() && pos.z >= 0 ))
			return false;
		if (!(pos.y < m_map[pos.z].size() && pos.y >= 0))
			return false;
		if (!(pos.x < m_map[pos.z][pos.y].size() && pos.x >= 0))
			return false;
		return true;
		
	}
	
	static std::vector<glm::vec3> dirs({ {0,0,-1},{0,0,1}, {0,-1,0},{0,1,0},{-1,0,0},{1,0,0} });
	std::vector<Pathfinding::cell*> Pathfinding::get_neighbours(const cell* current, const std::vector<cell*>& q_vector, std::vector<std::vector<std::vector<cell>>>& m_cellmap)
	{
		std::vector<cell*> neighbours;
		//LOG_DEBUG("current pos: x: {} y: {} z:{}", current->pos.x, current->pos.y, current->pos.z);
		for(auto dir : dirs)
		{
			glm::vec3 pos = current->pos + dir;
			//LOG_DEBUG("pos: x: {} y: {} z:{}",pos.x, pos.y, pos.z);
			//LOG_DEBUG("is_valid pos {}", is_valid(pos));
			if (is_valid(pos))
				neighbours.push_back(&m_cellmap[pos.z][pos.y][pos.x]);

		}
		return neighbours;
	}

	double Pathfinding::get_dist(cell* curr, const cell* dest)
	{
		switch (m_map[dest->pos.z][dest->pos.y][dest->pos.x])
		{
		case Cell::NOTHING:
			return 1;
			break;
		case Cell::WALL:
			return 50;
			break;
		case Cell::DEFENSE:
			return 25;
			break;
		case Cell::STAIR:
			return 1;
			break;
		default:
				return 1;
		}
		return 1;
	}
}
