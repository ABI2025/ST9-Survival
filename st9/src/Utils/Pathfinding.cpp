#include "Pathfinding.h"

#include <iostream>

#include "../Player.h"
#include "Utils.h"

namespace Utils {
	Pathfinding* Pathfinding::s_instance = nullptr;


	void Pathfinding::Init(std::shared_ptr<Player> i_player, std::vector<std::vector<std::vector<Utils::Cell>>>& i_map)
	{
		LOG_INFO("sizeof cell {}", sizeof(cell));
		if (!s_instance)
			s_instance = new Pathfinding(i_player, i_map);
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

	std::vector<glm::vec3> Pathfinding::find_path(const glm::vec3& start, Priority p)
	{

		/*	if(!m_player->is_alive() && p == Priority::player)
			{
				p = Priority::nothing;
			}*/
		switch (p)
		{
		case Priority::nothing:
			return make_path(start, nothing_cellmap);
			break;
		case Priority::tower:
			return make_path(start, tower_cellmap);
			break;

		case Priority::player:
			const glm::vec3 dest = m_player->get_pos();
			LOG_DEBUG("player: x:{} y:{} z:{}", dest.x, dest.y, dest.z);
			if (vec3_almost_equal(dest / 135.0f, start / 135.0f, 1.0f))
			{
				LOG_INFO("used brensenham");
				return bresenham(dest, start);
			}
			LOG_INFO("used backtracking");

			return make_path(start, player_cellmap);
			//return a_star(round(dest), round(start));
			break;


		}

		return {};

	}


	Pathfinding::Pathfinding(const std::shared_ptr<Player>& i_player, std::vector<std::vector<std::vector<Utils::Cell>>>& i_map)
		: m_player(i_player), m_map(i_map)
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

	std::vector<glm::vec3> Pathfinding::make_path(const glm::vec3& start,
		const std::vector<std::vector<std::vector<cell>>>& cellmap)
	{
		ScopedTimer ttt("backtrackening");
		glm::vec3 rounded_start = round(glm::vec3{ start.x / 135.0f,start.y / 135.0f,0 });
		std::vector<glm::vec3> bewegungsablauf; // hier wird der bewegungsablauf gespeichert
		if (!is_valid(rounded_start))
		{
			LOG_CRITICAL("das sollte nicht passieren");
#ifdef DEBUG
			//__debugbreak();
#endif
			return {};
		}
		const cell* u = &cellmap[rounded_start.z][rounded_start.y][rounded_start.x];
		//constexpr double epsilon = 1e-6; 
		if (u == nullptr)
		{
			LOG_CRITICAL("das sollte nicht passieren");
#ifdef DEBUG
			//__debugbreak();
#endif
			return {};
		}

		if (u->parent != nullptr)
		{
			for (auto pos : bresenham(start, u->parent->pos * 135.0f))
			{
				bewegungsablauf.push_back(pos);
			}
			u = u->parent;
		}
		else
		{
			for (auto pos : bresenham(start, u->pos * 135.0f))
			{
				bewegungsablauf.push_back(pos);
			}
			std::ranges::reverse(bewegungsablauf);
			return bewegungsablauf;
		}
		while (u->parent != nullptr)
		{
			if (u == nullptr)
			{
				LOG_CRITICAL("what ze fuck");
				std::cin.get();
			}
			for (auto pos : bresenham(u->pos * 135.0f, u->parent->pos * 135.0f))
			{
				bewegungsablauf.push_back(pos);
			}
			u = u->parent;
		}
		std::ranges::reverse(bewegungsablauf);
		return bewegungsablauf;
	}

	std::vector<glm::vec3> Pathfinding::a_star(const glm::vec3& dest, const glm::vec3& start)
	{
		ScopedTimer a_star_t("A*");
		const glm::vec3 rounded_dest = round(dest / 135.0f);
		const glm::vec3 rounded_start = round(start / 135.0f);

		if (!is_valid(rounded_dest) || !is_valid(rounded_start))
		{
			return bresenham(dest, start);
		}


		std::vector<std::vector<std::vector<cell>>> m_cellmap =
			std::vector(m_map.size(), std::vector(m_map[0].size(),
				std::vector(m_map[0][0].size(),
					cell{ {0,0,0},DBL_MAX,DBL_MAX,nullptr })));

		std::vector<cell*> q_vector; //eigentlich sollte man eine priority
		//queue nutzen aber es gibt damit probleme deshalb
		//ein vector und jedes mal sortiert kommt aufs selbe hinaus wie mit ner priority queue

		//alle positonen werden in q_vector geladen könnte noch mal optimiert werden
		for (int i = 0; i < m_map.size(); i++) // z
		{
			for (int j = 0; j < m_map[i].size(); j++) // y
			{
				for (int k = 0; k < m_map[i][j].size(); k++) // x
				{
					m_cellmap[i][j][k].pos = { k, j, i }; // x y z 
					const glm::vec3 temp = rounded_dest - glm::vec3(k, j, i);
					m_cellmap[i][j][k].h_dist = temp.x + temp.y; // h_dist ist die manhatten distanz zwischen einem punkt und der destination
					q_vector.push_back(&m_cellmap[i][j][k]); // hinzufugen der zelle zu q_vector

				}
			}
		}

		m_cellmap[rounded_start.z][rounded_start.y][rounded_start.x].dist = 0; //distanz am start zu 0 setzen als startpunkt

		auto comp = [](const cell* c1, const cell* c2)->bool //eine funktion um die zellen mit einander zu vergleichen
			{
				return (c1->dist + c1->h_dist) > (c2->dist + c2->h_dist);
			};

		int i = 5;
		while (!q_vector.empty())
		{
			std::sort(q_vector.begin(), q_vector.end(), comp); // sortieren. die zelle mit der niedrigsten distanz ist ganz hinten
			cell* u = q_vector.back(); // hinterstes element wird genommen
			q_vector.pop_back(); // aus dem vector gelöscht
			for (cell* v : get_neighbours(u, q_vector, m_cellmap)) // die nachbarn von u durchgehen
			{
				const double dist = u->dist + get_dist(u, v); //distanz ausrechnen zwischen u und v 
				if (dist < m_cellmap[v->pos.z][v->pos.y][v->pos.x].dist) // ist diese niedriger
				{
					m_cellmap[v->pos.z][v->pos.y][v->pos.x].dist = dist; // wird die distanz von v verändert
					m_cellmap[v->pos.z][v->pos.y][v->pos.x].parent = &m_cellmap[u->pos.z][u->pos.y][u->pos.x];// und u wird als parent von v gesetzt
				}
			}

			if (m_cellmap[rounded_dest.z][rounded_dest.y][rounded_dest.x].dist != DBL_MAX && m_cellmap[rounded_dest.z][rounded_dest.y][rounded_dest.x].parent != nullptr)
			{ //wenn die destination schon eine veränderte distanz hat und ein parent hat wird gestoppt
				break;
			}
		}
		ScopedTimer t("Backtracking");
		std::vector<glm::vec3> bewegungsablauf; // hier wird der bewegungsablauf gespeichert
		cell* u = &m_cellmap[rounded_dest.z][rounded_dest.y][rounded_dest.x];
		//constexpr double epsilon = 1e-6; 

		while (u->parent->parent != nullptr)
		{
			for (auto pos : bresenham(u->pos * 135.0f, u->parent->pos * 135.0f))
			{
				bewegungsablauf.push_back(pos);
			}
			u = u->parent;
		}
		for (auto pos : bresenham(u->pos * 135.0f, start))
		{
			bewegungsablauf.push_back(pos);
		}
		//std::ranges::reverse(bewegungsablauf);
		return bewegungsablauf;
	}

	std::vector<glm::vec3> Pathfinding::bresenham(const glm::vec3& dest, const glm::vec3& start)
	{
		glm::vec3 temp_dest = round(dest);
		glm::vec3 temp_start = round(start);

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

				route.emplace_back(x1, y1, 0.0f);

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


	bool Pathfinding::is_valid(const glm::vec3& pos) const
	{
		if (!(pos.z < m_map.size() && pos.z >= 0))
			return false;
		if (!(pos.y < m_map[pos.z].size() && pos.y >= 0))
			return false;
		if (!(pos.x < m_map[pos.z][pos.y].size() && pos.x >= 0))
			return false;
		return true;

	}

	void Pathfinding::calculate_paths()
	{
		//ScopedTimer calc_path("calculate_paths");
		//run dijkstra ez

		//priority player
		{
			//ScopedTimer player("priority player");
			const glm::ivec3 start = glm::ivec3(m_player->get_pos().x / 135.0f, m_player->get_pos().y / 135.0f, 0);
			if (!is_valid(start))
			{
				LOG_ERROR("das hätte nicht passieren sollen start: x:{} y:{} z:{}",
					start.x, start.y, start.z);

			}
			player_cellmap =
				std::vector(m_map.size(),
					std::vector(m_map[0].size(),
						std::vector(m_map[0][0].size(),
							cell{ {0,0,0},DBL_MAX,0,nullptr })));

			std::vector<cell*> q_vector; //eigentlich sollte man eine priority
			//queue nutzen aber es gibt damit probleme deshalb
			//ein vector und jedes mal sortiert kommt aufs selbe hinaus wie mit ner priority queue

			//alle positonen werden in q_vector geladen könnte noch mal optimiert werden
			for (int i = 0; i < m_map.size(); i++) // z
			{
				for (int j = 0; j < m_map[i].size(); j++) // y
				{
					for (int k = 0; k < m_map[i][j].size(); k++) // x
					{
						player_cellmap[i][j][k].pos = { k, j, i }; // x y z 
						q_vector.push_back(&player_cellmap[i][j][k]); // hinzufugen der zelle zu q_vector
					}
				}
			}
			if (!is_valid(start))
			{
				LOG_CRITICAL("das ist nicht gut");
			}
			else
			{
				player_cellmap[start.z][start.y][start.x].dist = 0; //distanz am start zu 0 setzen als startpunkt
				auto comp = [](const cell* c1, const cell* c2)->bool //eine funktion um die zellen mit einander zu vergleichen
					{
						return (c1->dist) > (c2->dist);
					};

				while (!q_vector.empty())
				{
					std::ranges::sort(q_vector, comp); // sortieren. die zelle mit der niedrigsten distanz ist ganz hinten
					cell* u = q_vector.back(); // hinterstes element wird genommen
					q_vector.pop_back(); // aus dem vector gelöscht
					for (const cell* v : get_neighbours(u, q_vector, player_cellmap)) // die nachbarn von u durchgehen
					{
						const double dist = u->dist + get_dist(u, v); //distanz ausrechnen zwischen u und v 
						if (dist < player_cellmap[v->pos.z][v->pos.y][v->pos.x].dist) // ist diese niedriger
						{
							player_cellmap[v->pos.z][v->pos.y][v->pos.x].dist = dist; // wird die distanz von v verändert
							player_cellmap[v->pos.z][v->pos.y][v->pos.x].parent = &player_cellmap[u->pos.z][u->pos.y][u->pos.x];// und u wird als parent von v gesetzt
						}
					}
				}
			}

			//for (int i = 0; i < m_map.size(); i++) // z
			//{
			//	for (int j = 0; j < m_map[i].size(); j++) // y
			//	{
			//		for (int k = 0; k < m_map[i][j].size(); k++) // x
			//		{
			//			cell* u = &player_cellmap[i][j][k]; // x y z 
			//			while(u->parent != nullptr)
			//			{
			//				u = u->parent;
			//			}
			//			LOG_DEBUG("start: x:{} y:{} z:{} u: x:{} y:{} z:{}", k, j, i, u->pos.x, u->pos.y, u->pos.z);
			//		}
			//	}
			//}
		}

		////priority nothing
		//{
		//	//ScopedTimer nothing("priority nothing");
		//	std::vector<glm::ivec3> start_points;
		//	//for(auto towers: get_alltowers())
		//	//{
		//	//	start_points.push_back(tower.get_pos()/135.0f);
		//	//}
		//	
		//	start_points.push_back((glm::ivec3(m_player->get_pos().x / 135.0f, m_player->get_pos().y / 135.0f, 0)));
		//	nothing_cellmap =
		//		std::vector(m_map.size(), std::vector(m_map[0].size(),
		//			std::vector(m_map[0][0].size(),
		//				cell{ {0,0,0},DBL_MAX,DBL_MAX,nullptr })));
		//	std::vector<cell*> q_vector; //eigentlich sollte man eine priority
		//	//queue nutzen aber es gibt damit probleme deshalb
		//	//ein vector und jedes mal sortiert kommt aufs selbe hinaus wie mit ner priority queue
		//	//alle positonen werden in q_vector geladen könnte noch mal optimiert werden
		//	for (int i = 0; i < m_map.size(); i++) // z
		//	{
		//		for (int j = 0; j < m_map[i].size(); j++) // y
		//		{
		//			for (int k = 0; k < m_map[i][j].size(); k++) // x
		//			{
		//				nothing_cellmap[i][j][k].pos = { k, j, i }; // x y z 
		//				q_vector.push_back(&nothing_cellmap[i][j][k]); // hinzufugen der zelle zu q_vector
		//			}
		//		}
		//	}
		//	auto comp = [](const cell* c1, const cell* c2)->bool //eine funktion um die zellen mit einander zu vergleichen
		//		{
		//			return (c1->dist) > (c2->dist);
		//		};
		//	for (glm::vec start : start_points)
		//	{
		//		nothing_cellmap[start.z][start.y][start.x].dist = 0; //distanz am start zu 0 setzen als startpunkt
		//		nothing_cellmap[start.z][start.y][start.x].parent = nullptr; //distanz am start zu 0 setzen als startpunk
		//	}
		//	while (!q_vector.empty())
		//	{
		//		std::sort(q_vector.begin(), q_vector.end(), comp); // sortieren. die zelle mit der niedrigsten distanz ist ganz hinten
		//		cell* u = q_vector.back(); // hinterstes element wird genommen
		//		q_vector.pop_back(); // aus dem vector gelöscht
		//		for (cell* v : get_neighbours(u, q_vector, nothing_cellmap)) // die nachbarn von u durchgehen
		//		{
		//			const double dist = u->dist + get_dist(u, v); //distanz ausrechnen zwischen u und v 
		//			if (dist < nothing_cellmap[v->pos.z][v->pos.y][v->pos.x].dist) // ist diese niedriger
		//			{
		//				nothing_cellmap[v->pos.z][v->pos.y][v->pos.x].dist = dist; // wird die distanz von v verändert
		//				nothing_cellmap[v->pos.z][v->pos.y][v->pos.x].parent = &nothing_cellmap[u->pos.z][u->pos.y][u->pos.x];// und u wird als parent von v gesetzt
		//			}
		//		}
		//	}
		//}

		////priority tower
		//{
		//	//ScopedTimer tower("priority tower");
		//	/*for(auto towers: get_alltower())
		//	{
		//		start_points.push_back(tower.get_pos()/135.0f);
		//	}
		//	*/
		//	std::vector<glm::ivec3> start_points;
		//	//for(auto towers: get_alltowers())
		//	//{
		//	//	start_points.push_back(tower.get_pos()/135.0f);
		//	//}
		//	if (start_points.empty() == true)
		//	{
		//		start_points.push_back((glm::ivec3(m_player->get_pos().x / 135.0f, m_player->get_pos().y / 135.0f, 0)));
		//	}
		//	{
		//		tower_cellmap =
		//			std::vector(m_map.size(), std::vector(m_map[0].size(),
		//				std::vector(m_map[0][0].size(),
		//					cell{ {0,0,0},DBL_MAX,DBL_MAX,nullptr })));
		//		std::vector<cell*> q_vector; //eigentlich sollte man eine priority
		//		//queue nutzen aber es gibt damit probleme deshalb
		//		//ein vector und jedes mal sortiert kommt aufs selbe hinaus wie mit ner priority queue
		//		//alle positonen werden in q_vector geladen könnte noch mal optimiert werden
		//		for (int i = 0; i < m_map.size(); i++) // z
		//		{
		//			for (int j = 0; j < m_map[i].size(); j++) // y
		//			{
		//				for (int k = 0; k < m_map[i][j].size(); k++) // x
		//				{
		//					tower_cellmap[i][j][k].pos = { k, j, i }; // x y z 
		//					q_vector.push_back(&tower_cellmap[i][j][k]); // hinzufugen der zelle zu q_vector
		//				}
		//			}
		//		}
		//		auto comp = [](const cell* c1, const cell* c2)->bool //eine funktion um die zellen mit einander zu vergleichen
		//			{
		//				return (c1->dist) > (c2->dist);
		//			};
		//		for (glm::vec start : start_points)
		//		{
		//			tower_cellmap[start.z][start.y][start.x].dist = 0; //distanz am start zu 0 setzen als startpunkt
		//			tower_cellmap[start.z][start.y][start.x].parent = nullptr; //distanz am start zu 0 setzen als startpunk
		//		}
		//		while (!q_vector.empty())
		//		{
		//			std::sort(q_vector.begin(), q_vector.end(), comp); // sortieren. die zelle mit der niedrigsten distanz ist ganz hinten
		//			cell* u = q_vector.back(); // hinterstes element wird genommen
		//			q_vector.pop_back(); // aus dem vector tower_cellmap
		//			for (cell* v : get_neighbours(u, q_vector, tower_cellmap)) // die nachbarn von u durchgehen
		//			{
		//				const double dist = u->dist + get_dist(u, v); //distanz ausrechnen zwischen u und v 
		//				if (dist < tower_cellmap[v->pos.z][v->pos.y][v->pos.x].dist) // ist diese niedriger
		//				{
		//					tower_cellmap[v->pos.z][v->pos.y][v->pos.x].dist = dist; // wird die distanz von v verändert
		//					tower_cellmap[v->pos.z][v->pos.y][v->pos.x].parent = &tower_cellmap[u->pos.z][u->pos.y][u->pos.x];// und u wird als parent von v gesetzt
		//				}
		//			}
		//		}
		//	}
		//}
	}

	static std::vector<glm::vec3> dirs({ {0,0,-1},{0,0,1}, {0,-1,0},{0,1,0},{-1,0,0},{1,0,0} });
	std::vector<Pathfinding::cell*> Pathfinding::get_neighbours(const cell* current, const std::vector<cell*>& q_vector, std::vector<std::vector<std::vector<cell>>>& m_cellmap)
	{
		std::vector<cell*> neighbours;
		//LOG_DEBUG("current pos: x: {} y: {} z:{}", current->pos.x, current->pos.y, current->pos.z);
		for (auto dir : dirs)
		{
			glm::vec3 pos = current->pos + dir;
			//LOG_DEBUG("pos: x: {} y: {} z:{}",pos.x, pos.y, pos.z);
			//LOG_DEBUG("is_valid pos {}", is_valid(pos));
			if (is_valid(pos))
				neighbours.push_back(&m_cellmap[(pos.z)][pos.y][pos.x]);

		}
		return neighbours;
	}

	double Pathfinding::get_dist(cell* curr, const cell* dest)
	{
		switch (m_map[dest->pos.z][dest->pos.y][dest->pos.x])
		{
		case Cell::NOTHING: // fallthrough
		case Cell::STAIR:
			return 1;

		case Cell::DEFENSE:
			return 2;

		case Cell::WALL:
			return 5;

		}
		return 1;
	}
}
