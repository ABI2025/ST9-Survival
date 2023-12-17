#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{

}

glm::vec3 Entity::get_pos()
{
	return m_pos;
}

void Entity::set_pos(glm::vec3 i_pos)
{
	m_pos = i_pos;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
