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
		if (vec3_almost_equal(round(dest),round(start)))
		{
			return bresenham(dest, start);
		}

		return a_star(round(dest), round(start));
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

	std::vector<glm::vec3> Pathfinding::a_star(const glm::vec3& dest, const glm::vec3& start)
	{
		const glm::vec3 rounded_dest = round(dest);
		const glm::vec3 rounded_start= round(start);
		if(!is_valid(rounded_dest) || !is_valid(rounded_start))
		{
			return bresenham(dest, start);
		}


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
					const glm::vec3 temp = rounded_dest - glm::vec3(k, j, i);
					m_cellmap[i][j][k].h_dist = temp.x+temp.y;
					q_vector.push_back(&m_cellmap[i][j][k]);
						
				}
			}
		}
		m_cellmap[rounded_start.z][rounded_start.y][rounded_start.x].dist = 0;





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
			if(m_cellmap[rounded_dest.z][rounded_dest.y][rounded_dest.x].dist != DBL_MAX && m_cellmap[rounded_dest.z][rounded_dest.y][rounded_dest.x].parent != nullptr)
			{
				i--;

			}
			if (i == 0)
				break;
		}

		std::vector<glm::vec3> bewegungsablauf;
		cell* u = &m_cellmap[rounded_dest.z][rounded_dest.y][rounded_dest.x];
		constexpr double epsilon = 1e-6;

		//for (int i = 0; i < (std::abs(rounded_start.y - u->pos.y) < epsilon ? 1 : 135); i++)
		//{

		//	for (int j = 0; j < (std::abs(rounded_start.x - u->pos.x) < epsilon ? 1 : 135); j++)
		//	{

		//		bewegungsablauf.push_back((start * 135.0f) - glm::vec3{ rounded_start.x > u->pos.x ? j : -j, rounded_start.y > u->pos.y ? i : -i,0 });
		//	}

		//}
		while (u->parent != nullptr)
		{
			for (int i = 0; i < (std::abs(u->parent->pos.y - u->pos.y) < epsilon ? 1 : 135); i++)
			{
					
				for (int j = 0; j < (std::abs(u->parent->pos.x - u->pos.x) < epsilon ? 1 : 135); j++)
				{
					
					bewegungsablauf.push_back((u->pos * 135.0f) - glm::vec3{ u->pos.x > u->parent->pos.x ? j : -j, u->pos.y > u->parent->pos.y ? i : -i,0 });
				}
				
			}
			u = u->parent;
		}
		//std::ranges::reverse(bewegungsablauf);
		return bewegungsablauf;
	}

	std::vector<glm::vec3> Pathfinding::bresenham(const glm::vec3& dest, const glm::vec3& start)
	{
		glm::vec3 temp_dest = round(dest * (135.0f));
		glm::vec3 temp_start = round(start * (135.0f));
		
		bool swapped = false;
		std::vector<glm::vec3> route;
		{
			int x1 = static_cast<int>(temp_start.x);
			int y1 = static_cast<int>(temp_start.y);
			int x2 = static_cast<int>(temp_dest.x);
			int y2 = static_cast<int>(temp_dest.y);

			// Ensure (x1, y1) is the point with the smaller x-coordinate
			if (x1 > x2) {
				swapped = true;
				std::swap(x1, x2);
				std::swap(y1, y2);
			}

			int dx = abs(x2 - x1);
			int dy = abs(y2 - y1);
			int sx = (x1 < x2) ? 1 : -1;
			int sy = (y1 < y2) ? 1 : -1;

			int err = dx - dy;

			while (true) {
				// Save the current point (x1, y1) to the vector
				route.push_back(glm::vec3(x1, y1, 0.0f));

				if (x1 == x2 && y1 == y2) {
					break;
				}

				int err2 = 2 * err;

				if (err2 > -dy) {
					err -= dy;
					x1 += sx;
				}

				if (err2 < dx) {
					err += dx;
					y1 += sy;
				}
			}
		}
		if (!swapped)
		{
			std::reverse(route.begin(), route.end());
		}
		return route;
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
