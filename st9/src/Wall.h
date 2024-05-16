#pragma once
#include "entities/entity/Entity.h"

class Wall : public Entity
{
public:
	Wall(glm::vec3 i_pos)
	{
		m_pos = i_pos;
		m_health = 500;
	}
};

