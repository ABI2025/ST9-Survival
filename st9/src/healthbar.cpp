#include "healthbar.h"
#include "entities/Player/Player.h"

healthbar::healthbar(double& i_health) : m_health(i_health)
{
	/*m_health = i_health;*/// Aktuelle HP - Standard HP 20
}

void healthbar::init(double& i_health)
{
	s_instance = new healthbar(i_health);
}

healthbar* healthbar::get_instance()
{
	return s_instance;
}

void healthbar::delete_instance()
{
	delete s_instance;
	s_instance = nullptr;
}

void healthbar::regeneration(const double health)
{// 

}
double healthbar::get_health() const
{
	return m_health;
}
bool healthbar::alive() const
{
	return m_health > 0;
}
bool healthbar::damage_input(const double damage)
{
	return true;
}
void healthbar::draw_healthbar(sf::RenderTarget& target, Player& p) const
{
	sf::RectangleShape background(sf::Vector2f(300, 40));
	background.setFillColor(sf::Color::White);
	background.setPosition(sf::Vector2f(target.getView().getCenter().x - target.getSize().x/2.0f + 50-4, target.getView().getCenter().y - target.getSize().y/2.0f + 50-4));
	sf::RectangleShape health_background(sf::Vector2f(292, 32));
	health_background.setFillColor(sf::Color::Black);
	health_background.setPosition(sf::Vector2f(target.getView().getCenter().x - target.getSize().x / 2.0f + 50, target.getView().getCenter().y - target.getSize().y / 2.0f + 50));
	sf::RectangleShape health(sf::Vector2f(static_cast<float>(292.0 * m_health / 200.0), 32.f));
	health.setFillColor(sf::Color::Red);
	health.setPosition(sf::Vector2f(target.getView().getCenter().x - target.getSize().x / 2.0f + 50, target.getView().getCenter().y - target.getSize().y / 2.0f + 50));
	target.draw(background);
	target.draw(health_background);
	target.draw(health);
}
