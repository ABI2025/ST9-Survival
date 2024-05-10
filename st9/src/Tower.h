#pragma once
#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"

class EnemyManager;

class Tower
{
	int m_ressourcen;
	double m_hp;
	double m_damage;
	glm::ivec3 m_pos;
	float condt{0};
	float cooldown = 0.5f;
	sf::Sprite sprites[2];
	sf::Texture textures[2];
public:
	Tower(glm::vec3);
	~Tower();
	void drawtower(sf::RenderTarget&) const;
	void fire(const EnemyManager& em, float deltatime);
	glm::vec3 get_pos()const { return m_pos; }
	//warten auf hinzufügen von projectile klasse


};

