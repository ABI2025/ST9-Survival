#pragma once


#include <memory>
#include <vector>
#include <glm/glm.hpp>


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
			double h_dist;
			cell* parent;
		};

		std::shared_ptr<Player> m_player;
		static Pathfinding* s_instance;
		std::vector<std::vector<std::vector<Cell>>>& m_map;
		//std::vector<std::vector<std::vector<cell>>> m_cellmap;


		//public methods
	public:
			/*
			* Init nimmt die Karte und den Player an und speichert sie als referenzen
			* 
			*
			*
			 */
			static void Init(std::shared_ptr<Player> i_player, std::vector<std::vector<std::vector<Cell>>>& i_map);

			//die klasse löschen, damit keine artifakte und sonstiges dableiben
			static void Delete();

			//Bevor get_instance gerufen wird, erstmal Init Rufen
			static Pathfinding* get_instance();

			
			std::vector<std::vector<std::vector<Cell>>>& get_map() const { return m_map; }

			glm::vec3 find_nearest(const glm::vec3& start, Priority priority);

			/*
			* dest ist das Ziel 
			*
			*
			* start ist der anfang (position vom gegner / entity)
			*
			*/
			std::vector<glm::vec3> find_path(const glm::vec3& dest, const glm::vec3& start);
			//private methods
					
			bool is_valid(const glm::vec3 &) const;
	private:
		std::vector<glm::vec3> a_star(const glm::vec3& dest, const glm::vec3& start);
		std::vector<glm::vec3> bresenham(const glm::vec3& dest, const glm::vec3& start);
		std::vector<cell*> get_neighbours(const cell*, const std::vector<cell*>&, std::vector<std::vector<std::vector<cell>>>& m_cellmap);
		double get_dist(cell *, const cell *);

	};

	


}
