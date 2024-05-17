#pragma once
#include <SFML/Graphics.hpp>
#include "entities/entity/Entity.h"
#include "glm/glm.hpp"

class EnemyManager;


//enum towerKind
//{
//	tower_1,
//	tower_2,
//	tower_3,
//	tower_4,
//	tower_5,
//	tower_6,
//	tower_7
//};



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
		if (!s_instance)
		{
			s_instance = new TowerTexture;
		}
		return s_instance;
	}
};

class Tower
	: public Entity
{
	int m_ressourcen;
	//double m_hp;
	double m_damage;
	float angle{};
	glm::vec3 prev_bullet_dir{ 1,0,0 };
	float cooldown = 0.8f;
	float condt{ 0.8f };
	sf::Sprite sprites[2];
	sf::Transform t;
public:
	Tower(glm::vec3);
	~Tower() override;
	void drawtower(sf::RenderTarget&) const;
	void fire(const EnemyManager& em, float deltatime);
	//glm::vec3 get_pos()const { return m_pos; }
	//warten auf hinzufügen von projectile klasse


};

