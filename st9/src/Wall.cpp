#include "Wall.h"

WallTexture::WallTexture()
{
		
	textures[0].loadFromFile("resources/images/1111.png");
	textures[1].loadFromFile("resources/images/1111mit rissen.png");
	textures[2].loadFromFile("resources/images/1111mit-mehr-rissen.png");
	textures[3].loadFromFile("resources/images/1111mit-viel-mehr-rissen.png");
}

WallTexture* WallTexture::get_instance()
{
	if (!s_instance)
	{
		s_instance = new WallTexture;
	}
	return s_instance;
}

void WallTexture::delete_instance()
{
	delete s_instance;
	s_instance = nullptr;
}

Wall::Wall(glm::vec3 i_pos)
{
	m_pos = i_pos;
	m_health = 2000;
	m_sprite.setTexture(WallTexture::get_instance()->textures[0]);
	m_sprite.setPosition(m_pos.x,m_pos.y);
}

void Wall::update()
{
	if (m_health < 500)
		m_sprite.setTexture(WallTexture::get_instance()->textures[3]);
	else if(m_health < 1000)
		m_sprite.setTexture(WallTexture::get_instance()->textures[2]);
	else if(m_health < 1500)
		m_sprite.setTexture(WallTexture::get_instance()->textures[1]);
	else
		m_sprite.setTexture(WallTexture::get_instance()->textures[0]);
}
