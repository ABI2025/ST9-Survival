#pragma once
#include "Entity.h"
class Player : public Entity
{
	sf::RectangleShape rec;
public:
	Player();
	void update();
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

