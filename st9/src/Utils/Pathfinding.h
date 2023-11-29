#pragma once
#include "Random.h"
#include <glm/glm.hpp>

#include "Utils.h"

class Player;

//nicht benutzen ist nicht fertig warte auf die Implementation von Player (soweit, dass ich mir wichtige daten holen kann)

namespace Utils
{
	/*

	class Pathfinding  
	{
		// Kunstruktor / destruktor

		
		Pathfinding(Player*);
	public:
		Pathfinding() = delete;
		Pathfinding(const Pathfinding&) = delete;
		Pathfinding(Pathfinding&&) = delete;
		Pathfinding& operator=(const Pathfinding& other) = delete;
		Pathfinding& operator=(Pathfinding&& other) = delete;


		~Pathfinding();
		//public methods
	public:
		//Init nimmt die Karte und den Player an und speichert sie als referenzen
		static void Init(Player*);
		static Pathfinding* get_instance();
		glm::vec3 find_nearest(glm::vec3 start, Priority);
		void find_path(glm::vec3 dest, glm::vec3 start);
		//private methods
		
	private:
		void dijkstra();


		//private member
	private:
		static Pathfinding* s_instance;
	
	};

	*/


}
