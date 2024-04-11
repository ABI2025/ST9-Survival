#pragma once
#include "Entity.h"
class Player : public Entity
{
public:
    Player();
    void update(float deltatime);
    glm::ivec3 getMovementSpeed() const; 

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    glm::ivec3 cell_pos;
    glm::ivec3 prev_cell_pos;
    glm::ivec3 prev_pos;
    int m_geld;
    double m_health;
    glm::ivec3 speed; 
};
