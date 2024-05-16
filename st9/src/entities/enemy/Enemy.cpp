#include "Enemy.h"
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "imgui.h"

constexpr glm::ivec2 enemy_size{ 135,135 };
constexpr glm::ivec2 enemy_sprite_sheet_length{ 4, 1 };
constexpr glm::ivec2 end{ enemy_size.x * enemy_sprite_sheet_length.x, enemy_size.y * enemy_sprite_sheet_length.y };

void Enemy::update()
{

}

bool Enemy::is_alive() const
{
	return m_health > 0;
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

void Enemy::attack()
{
	//wenn wir nen großen sprite sheet für enemy tot haben dann kann das hier auskommentiert werden
//if(!currently_dying){
//	//m_sprite.setTexture(death_sheet);
//	m_sprite.setTextureRect({{0,0},{enemy_size.x,enemy_size.y}});
//	currently_dying = true;
//	return;
//}
//auto& texture_rect = m_sprite.getTextureRect();
//const auto& texture_rect_pos = texture_rect.getPosition();
//if (texture_rect_pos == sf::Vector2i(ImVec2(end)))
//{
//	can_be_removed = true;
//}
//else if (texture_rect_pos.x == end.x) 
//{
//	m_sprite.setTextureRect({ {0, texture_rect_pos.y + enemy_size.y }, {enemy_size.x,enemy_size.y } });
//}
//else
//{
//	m_sprite.setTextureRect({ {texture_rect_pos.x + enemy_size.x, texture_rect_pos.y},{enemy_size.x,enemy_size.y} });
//}

}
