#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "Entity.h" // Include Entity instead of Enemy

class Projectile : public Entity { 
private:
    glm::vec3 m_speed; 
    int m_lifetime;

    inline static std::vector<Projectile*> projectiles;

public:
    Projectile(glm::vec3 pos, glm::vec3 speed, int lifetime);
    ~Projectile();

    void update();
    static void updateAll();
    static void drawAllProjectiles(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    static void cleanUp();
};