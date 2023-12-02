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
	
public:
	Entity();
	~Entity() override;
	glm::vec3 get_pos();
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

};