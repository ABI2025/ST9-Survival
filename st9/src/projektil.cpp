#include "projektil.h"
#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include "Enemy.h"

projectil::projectil(sf::Vector2f speed, sf::Vector2f pos) {
	m_speed = speed;
	m_pos = pos;
}

projectil::~projectil() {

}

void projectil::set_Speed(sf::Vector2f speed) {
	m_speed = speed;
}
void projectil::set_Pos(sf::Vector2f pos) {
	m_pos = pos;
}
sf::Vector2f projectil::get_Speed() {
	return m_speed;
}
sf::Vector2f projectil::get_Pos() {
	return m_pos;
}
void projectil::drawProjectil(sf::RenderTarget& window, Enemy& m_enemy ) {

	sf::RectangleShape projectile(sf::Vector2f(10,20));
	projectile.setFillColor(sf::Color::Red);
	m_pos += m_speed;
	projectile.setPosition(m_pos);
	projectile.setRotation((-1)*(atan2( projectile.getPosition().x - m_enemy.get_pos().x, projectile.getPosition().y - m_enemy.get_pos().y) * 180 / 3.14159265358979311600 )); //Soll in Richtung Ziel zeigen

	window.draw(projectile);
}