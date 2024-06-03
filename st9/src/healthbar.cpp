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
	sf::RectangleShape health(sf::Vector2f(abs(292.0f * sin(m_health) * tan(m_health) * cos(m_health)/* / 200.0f*/), 32));
	health.setFillColor(sf::Color::Magenta);
	health.setPosition(sf::Vector2f(target.getView().getCenter().x - target.getSize().x / 2.0f + 50, target.getView().getCenter().y - target.getSize().y / 2.0f + 50));
	target.draw(background);
	target.draw(health_background);
	target.draw(health);
}

//void healthbar::draw_healthbar(sf::RenderWindow& window, Player& p) {
//    // Constants for the health bar dimensions and offsets
//    const float healthBarWidth = 300.0f;
//    const float healthBarHeight = 40.0f;
//    const float borderThickness = 4.0f;  // border thickness around the health bar
//
//    // Calculate the position of the health bar based on the player's position
//    sf::Vector2f playerPos = { p.get_pos().x,p.get_pos().y };
//    sf::Vector2f healthBarPos = sf::Vector2f(playerPos.x - healthBarWidth / 2, playerPos.y - 50); // 50 pixels above the player
//
//    // Background for the health bar (white border)
//    sf::RectangleShape background(sf::Vector2f(healthBarWidth, healthBarHeight));
//    background.setFillColor(sf::Color::White);
//    background.setPosition(healthBarPos);
//
//    // Black background for the health portion
//    sf::RectangleShape health_background(sf::Vector2f(healthBarWidth - 2 * borderThickness, healthBarHeight - 2 * borderThickness));
//    health_background.setFillColor(sf::Color::Black);
//    health_background.setPosition(healthBarPos + sf::Vector2f(borderThickness, borderThickness));
//
//    // Health rectangle calculation
//    float healthPercentage = static_cast<float>(m_health) / 20.0f;  // Ensure float division
//    sf::RectangleShape health(sf::Vector2f((healthBarWidth - 2 * borderThickness) * healthPercentage, healthBarHeight - 2 * borderThickness));
//    health.setFillColor(sf::Color::Red);
//    health.setPosition(healthBarPos + sf::Vector2f(borderThickness, borderThickness));
//
//    // Draw the components to the window
//    window.draw(background);
//    window.draw(health_background);
//    window.draw(health);
//}
