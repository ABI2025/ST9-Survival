#include "Pathfinding.h"

namespace Utils {
	Utils::Pathfinding::Pathfinding()
	{
	}

	Pathfinding* Pathfinding::get_instance(Player*)
	{
		if (!s_instance)
			s_instance = new Pathfinding;
		return s_instance;
	}

	glm::vec3 Pathfinding::find_nearest(glm::vec3 start, Priority i_priority)
	{
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

	}

	Pathfinding::~Pathfinding()
	{

	}

	void Pathfinding::dijkstra()
	{

	}
}
