#pragma once


#include <glm/glm.hpp>

#include "Utils.h"

class Player;

//nicht benutzen ist nicht fertig warte auf die Implementation von Player (soweit, dass ich mir wichtige daten holen kann)

namespace Utils
{
	enum class Priority;
	enum class Cell;
	

	class Pathfinding  
	{
		// Kunstruktor / destruktor
		Pathfinding(const std::shared_ptr<Player>&, std::vector<std::vector<std::vector<Cell>>>& map);
	public:
		Pathfinding() = delete;
		Pathfinding(const Pathfinding&) = delete;
		Pathfinding(Pathfinding&&) = delete;
		Pathfinding& operator=(const Pathfinding& other) = delete;
		Pathfinding& operator=(Pathfinding&& other) = delete;


		~Pathfinding();
		//private member
	private:
		struct cell
		{
			glm::vec3 pos;
			double dist;
			cell* parent;
		};

		std::shared_ptr<Player> m_player;
		static Pathfinding* s_instance;
		std::vector<std::vector<std::vector<Cell>>>& m_map;
		//std::vector<std::vector<std::vector<cell>>> m_cellmap;


		//public methods
	public:
			//Init nimmt die Karte und den Player an und speichert sie als referenzen
			static void Init(std::shared_ptr<Player> i_player, std::vector<std::vector<std::vector<Cell>>>& i_map);
			static void Delete();
			static Pathfinding* get_instance();
			glm::vec3 find_nearest(const glm::vec3& start, Priority priority);
			std::vector<glm::vec3> find_path(const glm::vec3& dest, const glm::vec3& start);
			//private methods
					
	private:
		std::vector<glm::vec3> dijkstra(const glm::vec3& dest, const glm::vec3& start);
		bool is_valid(glm::vec3) const;
		std::vector<cell*> get_neighbours(const cell*, const std::vector<cell*>&, std::vector<std::vector<std::vector<cell>>> m_cellmap);
		double get_dist(cell *, const cell *);

	};

	


}
