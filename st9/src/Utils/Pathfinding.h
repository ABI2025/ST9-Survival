#pragma once
#include "Random.h"
#include <glm/glm.hpp>

#include "Utils.h"

class Player;


namespace Utils
{
	//nicht benutzen ist nicht fertig
	class Pathfinding  
	{
		static Pathfinding* s_instance;

		Pathfinding();
	public:
		//
		static void init(Player*);
		glm::vec3 find_nearest(glm::vec3 start, Priority);
		void find_path(glm::vec3 dest, glm::vec3 start);


		~Pathfinding();
	private:
		void dijkstra();


	public:
		Pathfinding(const Pathfinding&) = delete;
		Pathfinding(Pathfinding&&) = delete;
		Pathfinding& operator=(const Pathfinding& other) = delete;
		Pathfinding& operator=(Pathfinding&& other) = delete;
	};
}
