#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
class Entity : sf::Drawable
{
protected:
	glm::vec3 m_pos{};
	sf::Sprite m_sprite;
	//Utils::Priority m_priority; //für die gegner klasse
	glm::vec4 m_hitbox; // x relativ to m_pos , y relativ to m_pos, width , height
public:
	Entity();
	~Entity() override;
	glm::vec3 get_pos();
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

};