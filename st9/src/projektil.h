#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "Enemy.h"

class Projectile {
private:
    glm::vec2 m_pos;
    glm::vec2 m_speed;
    int m_lifetime;

    inline static std::vector<Projectile*> projectiles;

public:
    Projectile(glm::vec2 pos, glm::vec2 speed, int lifetime);
    ~Projectile();

    void update();
    static void updateAll();

    void drawProjectil(sf::RenderTarget&);
    static void drawALlProjectiles(sf::RenderTarget&);
    static void cleanUp();
};
