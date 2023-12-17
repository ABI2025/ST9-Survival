#pragma once
#include <chrono>
#include <execution>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
class Player;
class Camera
{
private:
	Player* m_player;
	sf::RenderWindow* m_window;
	sf::View m_view;
public:
	Camera(sf::RenderWindow* window);
	Camera(sf::RenderWindow* window, Player* player);
	~Camera();
	void set_player(Player* player);
	Player* get_player();
	void move_cam_to_player();
	void render();
	void move_to_pos(int x, int y);
	void move_to_pos(sf::Vector2f vec);
	void move_to_pos(sf::View view);
};