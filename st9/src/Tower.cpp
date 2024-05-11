// ReSharper disable CppTooWideScopeInitStatement
#include "Tower.h"
#include <cmath>
#include "entities/EnemyManager.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

constexpr glm::vec2 tower_sprite_center{69,55};


Tower::Tower(const glm::vec3 i_pos) : m_pos(i_pos)
{
	sprites[0].setTexture(TowerTexture::get_instance()->textures[0]);
	sprites[1].setTexture(TowerTexture::get_instance()->textures[1]);

	sprites[1].setPosition(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y));

	sprites[0].setOrigin
	   (sprites[0].getPosition().x + tower_sprite_center.x,
		sprites[0].getPosition().y + tower_sprite_center.y);

	sprites[0].setPosition
	   (static_cast<float>(m_pos.x)+ tower_sprite_center.x,
		static_cast<float>(m_pos.y) + tower_sprite_center.y);

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
	window.draw(sprites[1]);
	window.draw(sprites[0]);

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
			const glm::vec3 dir = glm::vec3{ closest_enemy ,0.0f } - static_cast<glm::vec3>(m_pos);
			if (dir != glm::vec3{0.0f,0.0f,0.0f})
			{
				const glm::vec3 bullet_dir = glm::normalize(dir);

				// Calculate the angle for rotation
				angle = std::atan2(bullet_dir.y, bullet_dir.x) * 180.0f / M_PI;
				angle -= 90;

				new Projectile({ static_cast<float>(m_pos.x) + 135.0f / 2.0f - 10.0f
					,static_cast<float>(m_pos.y) + 135.0f / 2.0f - 10.0f,0.0f },
					bullet_dir * 2.5f, 180, m_damage, 5);
			}
			else
			{
				angle = 0;
				new Projectile({ static_cast<float>(m_pos.x) + 135.0f / 2.0f - 10.0f
					,static_cast<float>(m_pos.y) + 135.0f / 2.0f - 10.0f,0.0f },
					glm::vec3{ 0.0f,1.0,0.0 } *2.5f, 180, m_damage, 5);
			}
			sprites[0].setRotation(angle); 
			condt = 0.0f;
		}
	}
	//sprites[0].rotate(1.0f);
	//if(sprites[0].getRotation() != angle)
	//	t.rotate(angle, { sprites[0].getPosition().x + 69,sprites[0].getPosition().y + 54});

}



			//auto hurensohn = glm::degrees(glm::atan(bullet_dir));
			//LOG_INFO("hurensohn: {} {} {}", hurensohn.x, hurensohn.y, hurensohn.z);