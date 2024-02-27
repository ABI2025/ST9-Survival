#include "projektil.h"
#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <math.h>

projectil::projectil(int speed, sf::Vector2f pos) {
	m_speed = speed;
	m_pos = pos;
}

projectil::~projectil() {

}

void projectil::setSpeed(int speed) {
	m_speed = speed;
}
void projectil::setVec2(sf::Vector2f pos) {
	m_pos = pos;
}
int projectil::getSpeed() {
	return m_speed;
}
sf::Vector2f projectil::getVec2() {
	return m_pos;
}
void projectil::drawProjectil(sf::RenderTarget& window, enemy& m_enemy ) {

	sf::RectangleShape projectile(sf::Vector2f(10,20));
	projectile.setFillColor(sf::Color::Red);
	projectile.setPosition(m_pos);
	//projectile.setRotation((-1)*(atan2( projectile.getPosition().x - m_enemy->get_pos().x, projectile.getPosition().y - m_enemy->get_pos().y) * 180 / 3.14159265358979311600)); //Soll in Richtung Ziel zeigen

	window.draw(projectile);
}