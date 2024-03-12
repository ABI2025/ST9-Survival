#pragma once
#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <list>
class Enemy;
class tower;
class projectil
{
private:
	sf::Vector2f m_pos{};
	int m_speed;
	static std::list<projectil*> projectiles;
	sf::Vector2f m_pos;
	sf::Vector2f m_speed;
public:
	projectil(sf::Vector2f, sf::Vector2f);
	~projectil();

	void setSpeed(int);
	void setPos(sf::Vector2f);
	void set_Speed(sf::Vector2f);
	void set_Pos(sf::Vector2f);

	sf::Vector2f get_Speed();
	sf::Vector2f get_Pos();

	void drawProjectil(sf::RenderTarget&,Enemy&); // ich werde diese funktion erstmal ignorieren.
	static void drawALlProjectiles(sf::RenderTarget& , Enemy&);
};

