#pragma once
#include "Entity.h"
class Player : public Entity
{
public:
	Player();
	void update(float deltatime);
protected:
	glm::ivec3 cell_pos;
	glm::ivec3 prev_cell_pos;
	glm::vec3 prev_pos;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int m_geld;
	double m_health;
	double m_movementSpeed;
};

