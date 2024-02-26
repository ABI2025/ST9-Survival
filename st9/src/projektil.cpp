#include "projektil.h"
#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

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
void projectil::drawProjectil(sf::RenderTarget& window) {
	sf::CircleShape projectile(10);
	//sf::RectangleShape projectile(sf::Vector2f(1,2));
	projectile.setFillColor(sf::Color::Red);
	projectile.setPosition(m_pos);
	//projectile.setRotation(); //Soll in Richtung Ziel zeigen

	window.draw(projectile);
}