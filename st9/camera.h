#pragma once
#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
class Player;
class camera
{
private:
	Player* pPtr;
	sf::RenderWindow* wPtr;
public:
	camera(sf::RenderWindow* window);
	camera(sf::RenderWindow* window, Player* player);
	~camera();
	void setPlayer(Player* player);
	Player* getPlayer();
	void moveCamToPlayer();
	void moveToPos(int x, int y);
	void moveToPos(sf::Vector2f vec);
	void moveToPos(sf::View view);
};