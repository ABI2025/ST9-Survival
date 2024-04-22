#include "healthbar.h"
#include "Player.h"

healthbar::healthbar() {
	m_health = 20;// Aktuelle HP - Standard HP 20
}
healthbar::~healthbar() {

}
void healthbar::regeneration(int health) {// 
	m_health += health;
}
int healthbar::get_health() {
	return m_health;
}
bool healthbar::alive() {
	if (m_health <= 0) {
		return false;
	}
	return true;
}
bool healthbar::damage_input(int damage) {
	m_health -= damage;
	if (m_health <= 0) {
		return false;
	}
	return true;
}
void healthbar::draw_healthbar(sf::RenderWindow& window, Player& p) {
	sf::RectangleShape background(sf::Vector2f(300,40));
	background.setFillColor(sf::Color::White);
	background.setPosition(sf::Vector2f(p.get_pos().x - window.getView().getSize().x / 2 + window.getView().getSize().x * 0.1 - 4, p.get_pos().y - window.getView().getSize().y / 2 + window.getView().getSize().y * 0.1 - 4));
	sf::RectangleShape health_background(sf::Vector2f(292, 32));
	health_background.setFillColor(sf::Color::Black);
	health_background.setPosition(sf::Vector2f(p.get_pos().x - window.getView().getSize().x / 2 + window.getView().getSize().x * 0.1, p.get_pos().y - window.getView().getSize().y / 2 + window.getView().getSize().y * 0.1));
	sf::RectangleShape health(sf::Vector2f(292*m_health/20, 32));
	health.setFillColor(sf::Color::Red);
	health.setPosition(sf::Vector2f(p.get_pos().x - window.getView().getSize().x/2 + window.getView().getSize().x * 0.1, p.get_pos().y - window.getView().getSize().y/2 + window.getView().getSize().y*0.1));
	window.draw(background);
	window.draw(health_background);
	window.draw(health);
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
