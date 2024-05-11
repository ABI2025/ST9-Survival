#pragma once
#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"

class EnemyManager;


class TowerTexture
{
	inline static TowerTexture* s_instance;
public:
	sf::Texture textures[2];
	TowerTexture()
	{
		textures[0].loadFromFile("resources/images/top.png");
		textures[1].loadFromFile("resources/images/buttom.png");
	}
	static TowerTexture* get_instance()
	{
		if(!s_instance)
		{
			s_instance = new TowerTexture;
		}
		return s_instance;
	}
};

class Tower
{
	int m_ressourcen;
	double m_hp;
	double m_damage;
	float angle{};
	glm::ivec3 m_pos;
	float cooldown = 0.5f;
	float condt{0.5f};
	sf::Sprite sprites[2];
	sf::Transform t;
public:
	Tower(glm::vec3);
	~Tower();
	void drawtower(sf::RenderTarget&) const;
	void fire(const EnemyManager& em, float deltatime);
	glm::vec3 get_pos()const { return m_pos; }
	//warten auf hinzufügen von projectile klasse


};

