#include "Projektil.h"
#include <algorithm>
#include "Utils/Log.h"

Projectile::Projectile(glm::vec3 pos, glm::vec3 speed, int lifetime) : Entity(), m_speed(speed), m_lifetime(lifetime) {
    set_pos(pos); // Use Entity's set_pos
    projectiles.push_back(this);
}

Projectile::~Projectile() {}

void Projectile::update() {
    glm::vec3 newPos = get_pos() + m_speed;
    set_pos(newPos);
    m_lifetime--;
}

void Projectile::draw(sf::RenderTarget& target , sf::RenderStates states) const {
    if (m_lifetime > 0) {
        sf::RectangleShape projectileShape(sf::Vector2f(10, 20));
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

void Projectile::drawAllProjectiles(sf::RenderTarget& target, sf::RenderStates states) {
    updateAll();
    for (Projectile* proj : projectiles) {
        if (proj != nullptr && proj->m_lifetime > 0) {
            proj->draw(target, states); // Use the inherited draw method
        }
    }
}