#pragma once
#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"
class Player;
class healthbar
{
private:
	double& m_health;
	healthbar(double&);
	inline static healthbar* s_instance;
public:

	static void init(double& i_health)
	{
		s_instance = new healthbar(i_health);
	}

	static healthbar* get_instance()
	{
		return s_instance;
	}

	static void delete_instance()
	{
		delete s_instance;
		s_instance = nullptr;
	}

	~healthbar() = default;
	void regeneration(double);

	[[nodiscard]] double get_health() const;

	bool damage_input(double);
	[[nodiscard]] bool alive() const;
	void draw_healthbar(sf::RenderTarget&, Player&) const;

};

