#include "projektil.h"
#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

projectil::projectil(int speed, glm::vec3 pos) {
	m_speed = speed;
	m_pos = pos;
}

projectil::~projectil() {

}

void projectil::setSpeed(int speed) {
	m_speed = speed;
}
void projectil::setVec3(glm::vec3 pos) {
	m_pos = pos;
}
int projectil::getSpeed() {
	return m_speed;
}
glm::vec3 projectil::getVec3() {
	return m_pos;
}