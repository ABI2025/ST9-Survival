#include "Projektil.h"
#include <algorithm>
#include "Utils/Log.h"

Projectile::Projectile(glm::vec3 pos, glm::vec3 speed, int lifetime , double damage , int penetration) : Entity(), m_speed(speed), m_lifetime(lifetime), m_damage(damage) , m_penetration(penetration) {
    set_pos(pos);
    projectiles.push_back(this);
}

Projectile::~Projectile() {}

void Projectile::update() {
    glm::vec3 newPos = get_pos() + m_speed;
    set_pos(newPos);
    m_lifetime--;
    this->m_hitbox = this->m_pos + glm::vec3{ 20,20,20 };
}

void Projectile::draw(sf::RenderTarget& target , sf::RenderStates states) const {
    if (m_lifetime > 0) {
        sf::RectangleShape projectileShape(sf::Vector2f(20, 20));
        projectileShape.setFillColor(sf::Color::Red);
        projectileShape.setPosition(get_pos().x, get_pos().y);
        target.draw(projectileShape,states);
    }
}

void Projectile::cleanUp() {
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](Projectile* p) {
            bool shouldRemove = p->m_lifetime <= 0;
            if (shouldRemove) {
                delete p;
            }
            return shouldRemove;
        }), projectiles.end());
}

void Projectile::updateAll() {
    for (Projectile* p : projectiles) {
        p->update();
    }
    cleanUp();
}

void Projectile::drawAllProjectiles(sf::RenderTarget& target, sf::RenderStates states) {//von Elias (Seinem ego gehts gut)
    updateAll();
    for (Projectile* proj : projectiles) {
        if (proj != nullptr && proj->m_lifetime > 0) {
            proj->draw(target, states);
        }
    }
}

void Projectile::removeProjectile(Projectile* projectile) {
    auto it = std::find(projectiles.begin(), projectiles.end(), projectile);
    if (it != projectiles.end()) {
        delete* it;
        projectiles.erase(it);
    }
}

void Projectile::decrease_penetration(int prenetationDecrease) {
    m_penetration -= prenetationDecrease;
}

double Projectile::get_damage() const {
    return m_damage; 
}
int Projectile::get_penetration() const {
    return m_penetration;
}
std::vector<Projectile*>& Projectile::get_projectiles(){
    return projectiles;
}