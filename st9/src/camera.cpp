#include "Camera.h"
#include "Player.h"

Camera::Camera(sf::RenderWindow* window) 
{
	m_window = window;
	m_player = nullptr;
}

Camera::Camera(sf::RenderWindow* window, Player* player)
{
	m_window = window;
	m_player = player;
}

Camera::~Camera()
{

}

void Camera::set_player(Player* player)
{
	m_player = player;
}

Player* Camera::get_player()
{
	return m_player;
}

void Camera::move_cam_to_player()
{
	m_window->setView(sf::View(sf::Vector2f(m_player->get_pos().x, m_player->get_pos().y), sf::Vector2f(1920, 1080)));	//Methode um die Player Position zu bekommen unbekant 
}

void Camera::move_to_pos(int x, int y)
{
	m_window->setView(sf::View(sf::Vector2f(x, y), sf::Vector2f(1920, 1080)));
}

void Camera::move_to_pos(sf::Vector2f v)
{
	m_window->setView(sf::View(v, sf::Vector2f(1920, 1080)));
}

void Camera::move_to_pos(sf::View v)
{
	m_window->setView(v);
}