#pragma once
#include "entities/entity/Entity.h"


class WallTexture
{
	inline static WallTexture* s_instance;
public:
	sf::Texture textures[4];
	WallTexture()
	{
		
		textures[0].loadFromFile("resources/images/1111.png");
		textures[1].loadFromFile("resources/images/1111mit rissen.png");
		textures[2].loadFromFile("resources/images/1111mit-mehr-rissen.png");
		textures[3].loadFromFile("resources/images/1111mit-viel-mehr-rissen.png");
	}
	static WallTexture* get_instance()
	{
		if (!s_instance)
		{
			s_instance = new WallTexture;
		}
		return s_instance;
	}

	static void delete_instance()
	{
		delete s_instance;
		s_instance = nullptr;
	}
};


class Wall : public Entity
{
	sf::Sprite m_sprite2;
public:
	explicit Wall(glm::vec3 i_pos)
	{
		m_pos = i_pos;
		m_health = 2000;
		m_sprite.setTexture(WallTexture::get_instance()->textures[0]);
		m_sprite.setPosition(m_pos.x,m_pos.y);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
			target.draw(m_sprite, states);
	}
	void update()override;

};

