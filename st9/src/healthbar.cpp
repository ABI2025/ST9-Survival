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
void healthbar::damage_input(int damage) {
	m_health -= damage;
	if (m_health <= 0) {
		//funktion die
	}
	return;
}
void healthbar::draw_healthbar(sf::RenderWindow& window, Player& p) {
	sf::RectangleShape background(sf::Vector2f(300,40));
	background.setFillColor(sf::Color::White);
	background.setPosition(sf::Vector2f(p.get_pos().x-800, p.get_pos().y-400));
	sf::RectangleShape health_background(sf::Vector2f(292, 32));
	health_background.setFillColor(sf::Color::Black);
	health_background.setPosition(sf::Vector2f(p.get_pos().x - 796, p.get_pos().y - 396));
	sf::RectangleShape health(sf::Vector2f(292 * (m_health / 20), 32));
	health.setFillColor(sf::Color::Red);
	health.setPosition(sf::Vector2f(p.get_pos().x-796, p.get_pos().y-396));
	window.draw(background);
	window.draw(health_background);
	window.draw(health);
}