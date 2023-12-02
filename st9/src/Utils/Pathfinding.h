#pragma once
#include "Random.h"
#include <glm/glm.hpp>

#include "Utils.h"

class Player;

//nicht benutzen ist nicht fertig warte auf die Implementation von Player (soweit, dass ich mir wichtige daten holen kann)

namespace Utils
{
	

	class Pathfinding  
	{
		// Kunstruktor / destruktor

		
		Pathfinding(Player*, std::vector<std::vector<std::vector<Utils::Cell>>>& map);
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

		Player* m_player;
		static Pathfinding* s_instance;
		std::vector<std::vector<std::vector<Utils::Cell>>>& m_map;
		std::vector<std::vector<std::vector<cell>>> m_cellmap;


		//public methods
	public:
			//Init nimmt die Karte und den Player an und speichert sie als referenzen
			static void Init(Player* i_player, std::vector<std::vector<std::vector<Utils::Cell>>>& i_map);
			static Pathfinding* get_instance();
			glm::vec3 find_nearest(const glm::vec3& start, Priority priority);
			void find_path(const glm::vec3& dest, const glm::vec3& start);
			//private methods
					
	private:
		void dijkstra(const glm::vec3& dest, const glm::vec3& start);
		bool is_valid(glm::vec3);
		std::vector<cell*> get_neighbours(const cell*, const std::vector<cell*>&);
		double get_dist(cell *, const cell *);

	};

	


}
