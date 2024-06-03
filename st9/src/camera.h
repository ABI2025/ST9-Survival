#pragma once
#include <SFML/Graphics.hpp>
class Player;
class Camera
{
public:
	explicit Camera(sf::RenderTarget* render_target);

	explicit Camera(sf::RenderTarget* render_target, Player* player);

	~Camera();

	const sf::FloatRect& get_player_view() const;

	void set_player(Player* player);

	void set_render_target(sf::RenderTarget* i_render_target);

	Player* get_player() const;

	void move_cam_to_player();

	void move_to_default();

	void set_window_size(int x, int y);

	void move_to_pos(int x, int y);

	void move_to_pos(sf::Vector2f vec);

	void move_to_pos(const sf::View& view);
private:
	Player* m_player;
	sf::RenderTarget* m_render_target;
	sf::View m_view;
};