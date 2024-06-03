#pragma once
#include "entities/entity/Entity.h"


class WallTexture
{
	inline static WallTexture* s_instance;
public:
	sf::Texture textures[4];
	WallTexture();

	static WallTexture* get_instance();

	static void delete_instance();
};


class Wall : public Entity
{
	sf::Sprite m_sprite2;
public:
	explicit Wall(glm::vec3 i_pos);

	void draw(sf::RenderTarget& target, const sf::RenderStates states) const override
	{
			target.draw(m_sprite, states);
	}
	void update(float)override;

};

