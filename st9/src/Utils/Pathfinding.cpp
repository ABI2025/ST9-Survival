#include "Pathfinding.h"

Utils::Pathfinding::Pathfinding()
{
}

void Utils::Pathfinding::init(Player*)
{
}

glm::vec3 Utils::Pathfinding::find_nearest(glm::vec3 start, Priority i_priority)
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

void Utils::Pathfinding::find_path(glm::vec3 dest, glm::vec3 start)
{

}

Utils::Pathfinding::~Pathfinding()
{

}

void Utils::Pathfinding::dijkstra()
{

}
