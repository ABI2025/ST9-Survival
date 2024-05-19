// ReSharper disable CppTooWideScopeInitStatement
#include "Tower.h"
#include <cmath>

#include "imgui.h"
#include "Sounds.h"
#include "entities/EnemyManager.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

constexpr glm::vec2 tower_sprite_center{ 135.f/2,135.f / 2 }; //danke simon für unsymmetrische texturen


Tower::Tower(const glm::vec3 i_pos)
{
	m_pos = i_pos;
	sprites[0].setTexture(TowerTexture::get_instance()->textures[0]);
	sprites[1].setTexture(TowerTexture::get_instance()->textures[1]);
	sprites[1].setPosition(m_pos.x, m_pos.y);

	sprites[0].setOrigin
	(sprites[0].getPosition().x + tower_sprite_center.x,
		sprites[0].getPosition().y + tower_sprite_center.y);

	sprites[0].setPosition
	(m_pos.x + tower_sprite_center.x,
		m_pos.y + tower_sprite_center.y);


	m_ressourcen = 0;
	m_health = 200;
	m_damage = 0.1;
}

Tower::Tower(glm::vec3 i_pos, float i_cooldown, double i_damage, double i_health)
{
	m_pos = i_pos;
	sprites[0].setTexture(TowerTexture::get_instance()->textures[0]);
	sprites[1].setTexture(TowerTexture::get_instance()->textures[1]);
	sprites[1].setPosition(m_pos.x, m_pos.y);

	sprites[0].setOrigin
	(sprites[0].getPosition().x + tower_sprite_center.x,
	 sprites[0].getPosition().y + tower_sprite_center.y);

	sprites[0].setPosition
	(m_pos.x + tower_sprite_center.x,
	 m_pos.y + tower_sprite_center.y);

	m_ressourcen = 0;

	m_cooldown = i_cooldown;
	m_condt = i_cooldown;
	m_health = i_health;
	m_damage = i_damage;
}


Tower::Tower(glm::vec3 i_pos, towerKind tower_kind,int ressourcen)
{
	m_pos = i_pos;
	sprites[0].setTexture(TowerTexture::get_instance()->textures[0]);
	sprites[1].setTexture(TowerTexture::get_instance()->textures[1]);
	sprites[1].setPosition(m_pos.x, m_pos.y);

	sprites[0].setOrigin
	(sprites[0].getPosition().x + tower_sprite_center.x,
		sprites[0].getPosition().y + tower_sprite_center.y);

	sprites[0].setPosition
	(m_pos.x + tower_sprite_center.x,
		m_pos.y + tower_sprite_center.y);
	m_ressourcen = ressourcen;

	switch (tower_kind)
	{
	case tower_1:
		m_health = 200;
		m_damage = 0.1;
		break;
	case tower_2:
		m_health = 300;
		m_damage = 0.1;
		break;
	case tower_3:
		m_health = 400;
		m_damage = 0.1;
		break;
	case tower_4:
		m_health = 500;
		m_damage = 0.1;
		break;
	case tower_5:
		m_health = 600;
		m_damage = 0.1;
		break;
	case tower_6:
		m_health = 700;
		m_damage = 0.1;
		break;
	default:
		break;
	}

}

Tower::~Tower()
= default;

void Tower::drawtower(sf::RenderTarget& window) const
{
	window.draw(sprites[1]);
	window.draw(sprites[0]);
}

void Tower::fire(const EnemyManager& em, Sounds& sound , const float deltatime)
{
	m_condt += deltatime;
	if (m_condt >= m_cooldown)
	{
		const glm::vec2 closest_enemy = { em.enemypos(6.0, m_pos) };
		if (closest_enemy != glm::vec2{ -1.0f,-1.0f })
		{
			const glm::vec3 dir = glm::vec3{ closest_enemy ,0.0f } - m_pos;
			//Prüfen ob der näheste gegner auf dem Turm ist

			const glm::vec2 position_center = glm::vec3{ tower_sprite_center,0 } + m_pos;
			const glm::vec2 position_for_bullet_to_spawn = position_center - glm::vec2{2.0f,12.5f};
			if (dir != glm::vec3{ 0.0f,0.0f,0.0f })
			{
				const glm::vec3 bullet_dir = glm::normalize(dir);
				m_prev_bullet_dir = bullet_dir;
				//winkel von dem Schuss berechnen damit der Turm richtig Rotiert ist
				m_angle = std::atan2(bullet_dir.y, bullet_dir.x) * 180.0f / M_PI;
				m_angle += 90;

				new Projectile({ position_for_bullet_to_spawn,0.0f },
					bullet_dir * 5.0f, 180, m_damage, 5);
			}
			else
			{
				//wenn der näheste gegner auf dem Turm ist nehmen wir die vorher gespeicherte rotierung und projektil Richtung
				new Projectile({ position_for_bullet_to_spawn ,0.0f },
					m_prev_bullet_dir * 5.0f, 180, m_damage, 5);
			}
			//const glm::vec3 player_pos = Utils::Pathfinding::get_instance()->get_player_pos();
			sound.add_sound("player", 2, m_pos);
			sprites[0].setRotation(m_angle);
			m_condt = 0.0f;
		}
	}

}




