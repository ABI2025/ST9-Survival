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