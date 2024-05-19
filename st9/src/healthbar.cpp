#include "healthbar.h"
#include "entities/Player/Player.h"

healthbar::healthbar()
{
	m_health = 20;// Aktuelle HP - Standard HP 20
}

void healthbar::regeneration(const int health)
{// 
	m_health += health;
	if (m_health > 20)
		m_health = 20;
}
int healthbar::get_health() const
{
	return m_health;
}
bool healthbar::alive() const
{
	return m_health > 0;
}
bool healthbar::damage_input(const int damage)
{
	if (m_health <= 0)
	{
		return false;
	}

	m_health -= damage;
	
	return true;
}
void healthbar::draw_healthbar(sf::RenderTarget& target, Player& p) const
{
	sf::RectangleShape background(sf::Vector2f(300, 40));
	background.setFillColor(sf::Color::White);
	background.setPosition(sf::Vector2f(p.get_pos().x - target.getView().getSize().x / 2.0f + target.getView().getSize().x * 0.1f - 4, p.get_pos().y - target.getView().getSize().y / 2.0f + target.getView().getSize().y * 0.1f - 4));
	sf::RectangleShape health_background(sf::Vector2f(292, 32));
	health_background.setFillColor(sf::Color::Black);
	health_background.setPosition(sf::Vector2f(p.get_pos().x - target.getView().getSize().x / 2.0f + target.getView().getSize().x * 0.1f, p.get_pos().y - target.getView().getSize().y / 2.0f + target.getView().getSize().y * 0.1f));
	sf::RectangleShape health(sf::Vector2f(292.0f * static_cast<float>(m_health) / 20.0f, 32));
	health.setFillColor(sf::Color::Red);
	health.setPosition(sf::Vector2f(p.get_pos().x - target.getView().getSize().x / 2 + target.getView().getSize().x * 0.1f, p.get_pos().y - target.getView().getSize().y / 2.0f + target.getView().getSize().y * 0.1f));
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
