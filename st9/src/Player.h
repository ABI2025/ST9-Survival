#pragma once
#include "Entity.h"
class Player : public Entity
{
public:
	Player();
	void update(float deltatime);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int geld;
	double health;
	double movementSpeed;
};

