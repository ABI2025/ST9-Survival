// ReSharper disable CppTooWideScopeInitStatement
#include "Tower.h"
#include <cmath>

#include "Game.h"
#include "imgui.h"
#include "Optionen.h"
#include "Sounds.h"
#include "entities/EnemyManager.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

constexpr glm::vec2 tower_sprite_center{ 135.f/2,135.f / 2 }; //danke simon f�r unsymmetrische texturen


TowerTexture::TowerTexture()
{
	base.loadFromFile("Resources/Images/tower_base.png");
	tops[0].loadFromFile("Resources/Images/top.png");
	tops[1].loadFromFile("Resources/Images/mg.png");
	tops[2].loadFromFile("Resources/Images/geld_raffinerie.png");
	tops[3].loadFromFile("Resources/Images/gold_mg.png");
	tops[4].loadFromFile("Resources/Images/Gold-Kanone.png");
	tops[5].loadFromFile("Resources/Images/Basic_Waffe.png");
}

TowerTexture* TowerTexture::get_instance()
{
	if (!s_instance)
	{
		s_instance = new TowerTexture;
	}
	return s_instance;
}

void TowerTexture::delete_instance()
{
	delete s_instance;
	s_instance = nullptr;
}

Tower::Tower(const glm::vec3 i_pos)
{
	m_pos = i_pos;
	sprites[0].setTexture(TowerTexture::get_instance()->tops[0]);
	sprites[1].setTexture(TowerTexture::get_instance()->base);
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
	is_not_economy = true;
}

Tower::Tower(const glm::vec3 i_pos, const float i_cooldown, const double i_damage, const double i_health)
{
	m_pos = i_pos;
	sprites[0].setTexture(TowerTexture::get_instance()->tops[0]);
	sprites[1].setTexture(TowerTexture::get_instance()->base);
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
	is_not_economy = true;

}


Tower::Tower(glm::vec3 i_pos, towerKind tower_kind,int ressourcen)
{
	m_pos = i_pos;

	sprites[1].setTexture(TowerTexture::get_instance()->base);
	sprites[1].setOrigin(tower_sprite_center.x, tower_sprite_center.y);
	sprites[1].setPosition(m_pos.x + tower_sprite_center.x, m_pos.y + tower_sprite_center.y);


	m_ressourcen = ressourcen;
	is_not_economy = true;
	switch (tower_kind)
	{
	case tower_1: // Basic
		m_health = 150;
		m_damage = 0.15;
		m_penetration = 5;
		m_speed = 6;
		sprites[0].setTexture(TowerTexture::get_instance()->tops[5]);
		break;
	case tower_2: // Maschienen gewehr
		m_health = 300;
		m_damage = 0.2;
		m_cooldown = 0.15f;
		m_penetration = 1;
		m_speed = 8;
		sprites[0].setTexture(TowerTexture::get_instance()->tops[1]);
		break;
	case tower_3: // Geld raffinerie
		is_not_economy = false;
		m_health = 400;
		m_damage = 25;
		m_cooldown = 2.0f;
		sprites[0].setTexture(TowerTexture::get_instance()->tops[2]);
		break;
	case tower_4: // Gold Maschienen Gewehr
		m_health = 1000;
		m_damage = 1;
		m_cooldown = 0.15f;
		m_penetration = 2;
		m_speed = 8;
		sprites[0].setTexture(TowerTexture::get_instance()->tops[3]);
		break;
	case tower_5: // Schwere Gold kanone
		m_health = 3000;
		m_damage = 2;
		m_cooldown = 1.3f;
		m_penetration = 30;
		m_speed = 4;
		m_radius = 20;
		sprites[0].setTexture(TowerTexture::get_instance()->tops[4]);
		break;
	case tower_6:
		m_health = 700;
		m_damage = 1.0;
		m_radius = 10;
		m_cooldown = 1.0f;
		m_speed = 5;
		sprites[0].setTexture(TowerTexture::get_instance()->tops[0]);
		break;
	default:
		break;
	}
	sprites[0].setOrigin
	(sprites[0].getPosition().x + tower_sprite_center.x,
		sprites[0].getPosition().y + tower_sprite_center.y);

	sprites[0].setPosition
	(m_pos.x + tower_sprite_center.x,
		m_pos.y + tower_sprite_center.y);
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
		if (is_not_economy) 
		{
			const glm::vec2 closest_enemy = { em.enemypos(m_radius, m_pos) };
			if (closest_enemy != glm::vec2{ -1.0f,-1.0f })
			{
				const glm::vec3 dir = glm::vec3{ closest_enemy ,0.0f } - m_pos;
				//Pr�fen ob der n�heste gegner auf dem Turm ist

				const glm::vec2 position_center = glm::vec3{ tower_sprite_center,0 } + m_pos;
				const glm::vec2 position_for_bullet_to_spawn = position_center - glm::vec2{ 2.0f,12.5f };
				if (dir != glm::vec3{ 0.0f,0.0f,0.0f })
				{
					const glm::vec3 bullet_dir = glm::normalize(dir);
					m_prev_bullet_dir = bullet_dir;
					//winkel von dem Schuss berechnen damit der Turm richtig Rotiert ist
					m_angle = std::atan2(bullet_dir.y, bullet_dir.x) * 180.0f / M_PI;
					m_angle += 90;

					new Projectile({ position_for_bullet_to_spawn,0.0f },
						bullet_dir * m_speed, 180, m_damage, m_penetration);
				}
				else
				{
					//wenn der n�heste gegner auf dem Turm ist nehmen wir die vorher gespeicherte rotierung und projektil Richtung
					new Projectile({ position_for_bullet_to_spawn ,0.0f },
						m_prev_bullet_dir * m_speed, 180, m_damage, m_penetration);
				}
				//const glm::vec3 player_pos = Utils::Pathfinding::get_instance()->get_player_pos();
				sound.add_sound("player", 2, m_pos);
				sprites[0].setRotation(m_angle);
			}
		}
		else
		{
			Game::get_game()->add_geld(m_damage);
		}

		m_condt = 0.0f;
	}
	if (Optionen::get_instance()->get_should_rotate()) 
	{
		sprites[0].rotate(36 * deltatime);
		sprites[1].rotate(36 * deltatime);
	}
	else
	{
		sprites[0].setRotation(m_angle);
		sprites[1].setRotation(0);
	}
}

void Tower::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	if(is_not_economy)
		target.draw(sprites[1],states);
	target.draw(sprites[0],states);
}

double Tower::get_value() const
{
	return m_ressourcen;
}




