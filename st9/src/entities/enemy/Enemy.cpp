#include "Enemy.h"
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

constexpr sf::Vector2i enemy_size(135,135);
constexpr sf::Vector2i end(enemy_size.x*4, enemy_size.y);

void Enemy::update()
{

}

bool Enemy::is_alive() const
{
	return m_health > 0;
}


double Enemy::get_hp() const
{
    return m_health;
}

Enemy::Enemy(): m_priority()
{
	m_health = 2;
}

void Enemy::die()
{
	can_be_removed = true;

	////wenn wir nen großen sprite sheet für enemy tot haben dann kann das hier auskommentiert werden
	//if(!currently_dying){
	//	m_sprite.setTexture(death_sheet);
	//  m_sprite.setTextureRect({{0,0},enemy_size});
	//	currently_dying = true;
	//	return;
	//}
	//auto& texture_rect = m_sprite.getTextureRect();
	//const auto& texture_rect_pos = texture_rect.getPosition();
	//if (texture_rect_pos == end)
	//{
	//	can_be_removed = true;
	//}
	//else if (texture_rect_pos.x == end.x) 
	//{
	//	m_sprite.setTextureRect({ {0, texture_rect_pos.y + enemy_size.y }, enemy_size });
	//}
	//else
	//{
	//	m_sprite.setTextureRect({ {texture_rect_pos.x + enemy_size.x, texture_rect_pos.y},enemy_size });
	//}
}
