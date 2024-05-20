#include "Wall.h"

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
