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
	int m_speed;
public:
	projectil(int);
	~projectil();

	void setSpeed(int);

	int getSpeed();
};

