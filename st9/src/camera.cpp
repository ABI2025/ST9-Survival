#include "Camera.h"
#include "entities/Player/Player.h"

Camera::Camera(sf::RenderTarget* render_target)
	:m_player(nullptr), m_render_target(render_target)
{
	m_view = sf::View({ 0,0 }, { static_cast<float>(m_render_target->getSize().x),static_cast<float>(m_render_target->getSize().y) });
}

Camera::Camera(sf::RenderTarget* render_target, Player* player)
	:m_player(player), m_render_target(render_target)
{
	m_render_target = render_target;
	m_player = player;
	m_view = sf::View({ 0,0 }, { static_cast<float>(m_render_target->getSize().x),static_cast<float>(m_render_target->getSize().y) });
}

Camera::~Camera()
{
}

void Camera::set_player(Player* player)
{
	m_player = player;
}

void Camera::set_RenderTarget(sf::RenderTarget* i_render_target)
{
	m_render_target = i_render_target;
}

Player* Camera::get_player()
{
	return m_player;
}

void Camera::move_cam_to_player()
{
	m_view.setCenter(m_player->get_pos().x + 50, m_player->get_pos().y + 50);
	m_view.setSize({static_cast<float>(m_render_target->getSize().x),static_cast<float>(m_render_target->getSize().y)});
	m_render_target->setView(m_view);
}

void Camera::move_to_default()
{
	m_view.setCenter(static_cast<float>(m_render_target->getSize().x)/2, static_cast<float>(m_render_target->getSize().y)/2);
	m_view.setSize({ static_cast<float>(m_render_target->getSize().x),static_cast<float>(m_render_target->getSize().y) });
	m_render_target->setView(m_view);
}

void Camera::set_window_size(const int x, const int y)
{
	m_view.setSize(static_cast<float>(x), static_cast<float>(y));
	m_render_target->setView(m_view);
}

void Camera::move_to_pos(const int x, const int y)
{
	m_view.setCenter(static_cast<float>(x),static_cast<float>(y));
	m_view.setSize({ static_cast<float>(m_render_target->getSize().x),static_cast<float>(m_render_target->getSize().y) });
	m_render_target->setView(m_view);
}

void Camera::move_to_pos(const sf::Vector2f vec)
{
	m_view.setCenter(vec);
	m_view.setSize({ static_cast<float>(m_render_target->getSize().x),static_cast<float>(m_render_target->getSize().y) });
	m_render_target->setView(m_view);
}

void Camera::move_to_pos(const sf::View& view)
{
	m_view = view;
	m_view.setSize({ static_cast<float>(m_render_target->getSize().x),static_cast<float>(m_render_target->getSize().y) });
	m_render_target->setView(m_view);
}