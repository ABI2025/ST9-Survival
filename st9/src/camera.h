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
	sf::RenderTarget* m_render_target;
	sf::View m_view;
public:
	explicit Camera(sf::RenderTarget* window);

	explicit Camera(sf::RenderTarget* window, Player* player);

	~Camera();

	const sf::FloatRect& get_player_view() const { return m_view.getViewport(); }

	void set_player(Player* player);

	void set_RenderTarget(sf::RenderTarget* i_render_target);

	Player* get_player();

	void move_cam_to_player();

	void move_to_default();

	void set_window_size(int x, int y);

	void move_to_pos(int x, int y);

	void move_to_pos(sf::Vector2f vec);

	void move_to_pos(const sf::View& view);
};