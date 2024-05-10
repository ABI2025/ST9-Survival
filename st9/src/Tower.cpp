// ReSharper disable CppTooWideScopeInitStatement
#include "Tower.h"

#include "entities/EnemyManager.h"

Tower::Tower(const glm::vec3 i_pos) : m_pos(i_pos)
{

	//textures[0].loadFromFile("resources/images/top.png");
	//textures[1].loadFromFile("resources/images/buttom.png");
	//sprites[0].setTexture(textures[0]);
	//sprites[1].setTexture(textures[1]);
	//sprites[0].setPosition(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y));
	//sprites[1].setPosition(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y));
	//sprites[0].setOrigin(135.0f / 2.0f, 135.0f / 2.0f);
	m_ressourcen = 0;
	m_hp = 1;
	m_damage = 0.1;
	//m_pos = {0.0f,0.0f};
}

Tower::~Tower()
= default;

void Tower::drawtower(sf::RenderTarget& window) const
{

	//rectangle.setPosition(m_pos);+
	
	//sprites[0].setPosition(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y));
	//sprites[1].setPosition(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y));
	//window.draw(sprites[1]);
	//window.draw(sprites[0]);

}

void Tower::fire(const EnemyManager& em, const float deltatime)
{
	condt += deltatime;
	//LOG_INFO("Closest_enemy: {} {} ", closest_enemy.x, closest_enemy.y);
	if (condt >= cooldown)
	{
		const glm::vec2 closest_enemy = { em.enemypos(10.0, m_pos) };
		if (closest_enemy != glm::vec2{ -1.0f,-1.0f })
		{
			const glm::vec3 bullet_dir = glm::normalize(glm::vec3{ closest_enemy,0.0f } - static_cast<glm::vec3>(m_pos));
			//LOG_INFO("Bullet dir: {} {} {}", bullet_dir.x, bullet_dir.y, bullet_dir.z);
			new Projectile({ static_cast<float>(m_pos.x) + 135.0f / 2.0f - 10.0f,static_cast<float>(m_pos.y) + 135.0f / 2.0f - 10.0f,0.0f }, 
				bullet_dir * 2.5f, 180, m_damage, 5);
			//auto hurensohn = glm::degrees(glm::atan(bullet_dir));
			//LOG_INFO("hurensohn: {} {} {}", hurensohn.x, hurensohn.y, hurensohn.z);
			//sprites[0].setRotation(degrees);
			condt = 0.0f;
		}
	}
}


