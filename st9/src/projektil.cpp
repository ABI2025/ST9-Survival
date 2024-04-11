#include "projektil.h"
#include <algorithm>
#include "Utils/Log.h"

Projectile::Projectile(glm::vec2 pos, glm::vec2 speed, int lifetime) : m_pos(pos), m_speed(speed), m_lifetime(lifetime) {
    projectiles.push_back(this);
}

Projectile::~Projectile() {}

void Projectile::update() {
    m_pos += m_speed; 
    m_lifetime--;     
}

void Projectile::updateAll() { // das können wir nutzen wenn wir frames skippen
    for (Projectile* p : projectiles) {
        p->update();
    }

    cleanUp();
}

void Projectile::drawProjectil(sf::RenderTarget& target) {
    if (m_lifetime > 0) {
        sf::RectangleShape projectileShape(sf::Vector2f(10, 20));
        projectileShape.setFillColor(sf::Color::Red);
        projectileShape.setPosition(m_pos.x, m_pos.y);
        target.draw(projectileShape);
    }
    
}

void Projectile::cleanUp() {
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](Projectile* p) {
            bool shouldRemove = p->m_lifetime <= 0;
            if (shouldRemove) {
                delete p; // Lösche das Objekt
            }
            return shouldRemove; // Gibt zurück, ob das Element entfernt werden soll
        }), projectiles.end());
}


void Projectile::drawALlProjectiles(sf::RenderTarget& target) { // das muss jeden frame ausgeführt werden
    for (Projectile* proj : projectiles) {
        if (proj != nullptr && proj->m_lifetime > 0) {
            proj->update();    
            proj->drawProjectil(target); 
        }
    }

    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](const Projectile* p) { return p->m_lifetime <= 0; }), projectiles.end());
}