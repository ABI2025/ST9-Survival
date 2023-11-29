#include "Pathfinding.h"


/*
namespace Utils {
	Pathfinding* Pathfinding::s_instance = nullptr;


	void Pathfinding::Init(Player*)
	{
		s_instance = new Pathfinding();
	}


	Pathfinding* Pathfinding::get_instance()
	{
		if (!s_instance)
			throw std::exception("Pathfinding::Init muss vor Pathfinding::get_instance() gerufen werden");
		return s_instance;
	}

	glm::vec3 Pathfinding::find_nearest(glm::vec3 start, Priority i_priority)
	{
		dijkstra();
		switch (i_priority)
		{
		case Priority::nothing: break;
		case Priority::player:
			return { 0, 0, 0 };
			break;
		case Priority::tower: break;
		}
		return { -1,-1,-1 };
	}

	void Pathfinding::find_path(glm::vec3 dest, glm::vec3 start)
	{
		dijkstra();
	}

	
	Pathfinding::~Pathfinding() = default;

	void Pathfinding::dijkstra()
	{
		
	}
}
*/