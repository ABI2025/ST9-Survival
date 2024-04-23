#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "Utils/Pathfinding.h"


class Entity : public sf::Drawable
{
protected:
	glm::vec3 m_pos{};
	sf::Sprite m_sprite;
	std::vector<std::vector<std::vector<sf::Texture>>> m_textures;
	//Utils::Priority m_priority; //für die gegner klasse
	glm::vec3 m_hitbox; // buttom right
	friend class Utils::Pathfinding;
	friend class EnemyManager;
public:
	Entity();
	~Entity() override;
	glm::vec3 get_pos() const;
	void set_pos(glm::vec3 i_pos);
	sf::Sprite& get_sprite();
	glm::vec3 get_hitBox() const;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

};
