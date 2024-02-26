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
	sf::Vector2f m_pos{};
	int m_speed;
public:
	projectil(int, sf::Vector2f);
	~projectil();

	void setSpeed(int);
	void setVec2(sf::Vector2f);

	int getSpeed();
	sf::Vector2f getVec2();
};

