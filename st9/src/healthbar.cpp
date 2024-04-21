#include "healthbar.h"

healthbar::healthbar(int health) {
	m_health = health;
}
healthbar::~healthbar() {

}
void healthbar::set_health(int health) {
	m_health = health;
}
int healthbar::get_health() {
	return m_health;
}
void healthbar::damage_input(int damage) {
	m_health -= damage;
}