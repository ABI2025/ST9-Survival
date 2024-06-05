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

Utils::Priority Enemy::get_priority() const
{
	return m_priority;
}


double Enemy::get_damage() const
{
	return m_damage;
}

Enemy::Enemy() : m_priority()
{
	m_health = 2;
	m_speed = 1;
	m_damage = 0.1;
}

void Enemy::die()
{
	can_be_removed = true;
}

void Enemy::attack()
{

}
