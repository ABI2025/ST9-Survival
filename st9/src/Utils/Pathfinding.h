#pragma once


#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "entities/Player/Player.h"


class Tower;

namespace Utils
{
	enum class Priority;
	enum class Cell;

	//Pathfinding ist ein Singleton
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

		//simple zell Struktur zum speichern von Daten beim Pathfinden
		struct cell
		{
			glm::ivec3 pos;
			double dist;
			//double h_dist;
			cell* parent;
		};

		std::shared_ptr<Player> m_player;
		static Pathfinding* s_instance;
		const std::vector<std::vector<std::vector<Cell>>>& m_map;
		std::vector<std::vector<std::vector<cell>>> m_player_cellmap;
		std::vector<std::vector<std::vector<cell>>> m_tower_cellmap;
		std::vector<std::vector<std::vector<cell>>> m_nothing_cellmap;


		//public methods
	public:
		/*
		 Init nimmt die Karte und den Player an und speichert sie als referenzen
		
		
		
		 */
		static void Init(std::shared_ptr<Player> i_player, std::vector<std::vector<std::vector<Cell>>>& i_map);

		// Die klasse loeschen, damit keine artifakte und sonstiges dableiben
		static void Delete();

		// Zuerst Init rufen sonst funktioniert nichts
		static Pathfinding* get_instance();


		[[nodiscard]] const std::vector<std::vector<std::vector<Cell>>>& get_map() const { return m_map; }


		/*
		
		 start ist der anfang (position vom gegner / entity)
		 Priority ist auf was der gegner/entity gehen soll
		 Moegliche Prioritaeten sind
		 Player 
		 Nothing
		 Tower
		 */
		[[nodiscard]] std::vector<glm::vec3> find_path(const glm::vec3& start, Priority) const;

		[[nodiscard]] bool is_valid(const glm::vec3&) const;

		void calculate_paths(std::vector<Tower>& towers);


		//private methods
	private:
		[[nodiscard]] std::vector<glm::vec3>	make_path(const glm::vec3& start, const std::vector<std::vector<std::vector<cell>>>& cellmap) const;
					  void						dijkstra(const std::vector<glm::ivec3>& start, std::vector<std::vector<std::vector<cell>>>& cellmap);
		[[nodiscard]] std::vector<glm::vec3>	bresenham(const glm::vec3& dest, const glm::vec3& start) const;
		[[nodiscard]] std::vector<cell*>		get_neighbours(const cell*, std::vector<std::vector<std::vector<cell>>>& m_cellmap) const;
		[[nodiscard]] double					get_dist(cell*, const cell*) const;

	};




}
