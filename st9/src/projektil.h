#pragma once
#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
class enemy;
class tower;
class projectil
{
private:
	glm::vec3 m_pos;
	int m_speed;
public:
	projectil(int, glm::vec3);
	~projectil();

	void setSpeed(int);
	void setVec3(glm::vec3);

	int getSpeed();
	glm::Vec3 getVec3();
};

