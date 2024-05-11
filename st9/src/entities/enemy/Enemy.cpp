#include "Enemy.h"
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

void Enemy::update()
{
}
bool Enemy::is_alive() const
{
	return m_health > 0;
}

void Enemy::take_damage(const double damage) {
    m_health -= damage;
    if (m_health <= 0) {
        die();
    }
}
double Enemy::get_hp() const
{
    return m_health;
}
void Enemy::die() {}