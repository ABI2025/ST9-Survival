#include "projektil.h"
#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include "Enemy.h"

projectil::projectil(int speed, sf::Vector2f pos) {
	m_speed = speed;
	m_pos = pos;
}

projectil::~projectil() {

}

void projectil::setSpeed(int speed) {
	m_speed = speed;
}
void projectil::setPos(sf::Vector2f pos) {
	m_pos = pos;
}
int projectil::getSpeed() {
	return m_speed;
}
sf::Vector2f projectil::getVec2() {
	return m_pos;
}
void projectil::drawProjectil(sf::RenderTarget& window, Enemy& m_enemy ) {
	sf::RectangleShape projectile(sf::Vector2f(10,20));
	projectile.setFillColor(sf::Color::Red);
	projectile.setPosition(m_pos);
	constexpr double temp = 180 / 3.14159265358979311600; // das sichert performance, weil diese operation extrem painfull für computern ist
	projectile.setRotation((-1)*(atan2( projectile.getPosition().x - m_enemy.get_pos().x, projectile.getPosition().y - m_enemy.get_pos().y) * temp )); //Soll in Richtung Ziel zeigen

	window.draw(projectile);
}

void projectil::drawALlProjectiles(sf::RenderTarget& window, Enemy& m_enemy)
{
	for (projectil* p : projectiles) {
		sf::RectangleShape projectile(sf::Vector2f(10, 20));
		projectile.setFillColor(sf::Color::Red);
		projectile.setPosition(m_pos);
		constexpr double temp = 180 / 3.14159265358979311600; // das sichert performance, weil diese operation extrem painfull für computern ist
		projectile.setRotation((-1) * (atan2(projectile.getPosition().x - m_enemy.get_pos().x, projectile.getPosition().y - m_enemy.get_pos().y) * temp)); //Soll in Richtung Ziel zeigen

		window.draw(projectile);
	}
}
