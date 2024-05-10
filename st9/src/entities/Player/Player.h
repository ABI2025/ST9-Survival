#pragma once
#include "entities/entity/Entity.h"

class Sounds;

class Player : public Entity
{
public:
    Player();
    void update(float deltatime);
    void shoot(float deltatime, Sounds& i_sounds, glm::vec3 mouse_pos);
    glm::ivec3 get_movement_speed() const; 

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    glm::ivec3 cell_pos{};
    glm::ivec3 prev_cell_pos{};
    glm::ivec3 prev_pos;
    int m_geld;
    double m_health;
    glm::ivec3 speed; 
};
