#include "Entity.h"
#include <fstream>
#include <iostream>

#include "Utils/Log.h"

Entity::Entity() {
}
Entity::~Entity()
{

}

glm::vec3 Entity::get_pos() const
{
	return m_pos;
}

void Entity::set_pos(const glm::vec3 i_pos)
{
	m_pos = i_pos;
}

sf::Sprite& Entity::get_sprite()
{
	return m_sprite;
}

glm::vec3 Entity::get_hit_box() const
{
	return m_hitbox;
}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}


void Entity::take_damage(const double damage)
{
	
	m_health -= damage;
	if (m_health < 0)
		m_health = 0;

}

double& Entity::get_hp() 
{
	return m_health;
}
