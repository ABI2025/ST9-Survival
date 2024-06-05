#include "Player.h"
#include "Utils/Log.h"
#include <iostream>

#include "healthbar.h"
#include "entities/EnemyManager.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Sounds.h"

Player::Player()
	: Entity(), prev_pos(), m_geld(0), speed()

{
	m_pos = { 720, 720, 0 };
	cell_pos = m_pos / 135.0f;
	prev_cell_pos = m_pos / 135.0f;
	m_textures.resize(2);
	for (auto& t : m_textures)
	{
		t.resize(3);
		for (auto& tt : t)
		{
			tt.resize(3);
		}
	}

	m_textures[0][0][0].loadFromFile("Resources/Images/charakter_L.png");
	m_textures[0][0][1].loadFromFile("Resources/Images/charakter_L1.png");
	m_textures[0][0][2].loadFromFile("Resources/Images/charakter_L2.png");

	m_textures[0][1][0].loadFromFile("Resources/Images/charakter_R.png");
	m_textures[0][1][1].loadFromFile("Resources/Images/charakter_R1.png");
	m_textures[0][1][2].loadFromFile("Resources/Images/charakter_R2.png");

	m_textures[1][0][0].loadFromFile("Resources/Images/charakter_HL.png");
	m_textures[1][0][1].loadFromFile("Resources/Images/charakter_HL1.png");
	m_textures[1][0][2].loadFromFile("Resources/Images/charakter_HL2.png");

	m_textures[1][1][0].loadFromFile("Resources/Images/charakter_HR.png");
	m_textures[1][1][1].loadFromFile("Resources/Images/charakter_HR1.png");
	m_textures[1][1][2].loadFromFile("Resources/Images/charakter_HR2.png");
	m_sprite.setTexture(m_textures[0][0][0]);
	m_hitbox = m_pos + glm::vec3{ 35,117,0 };
	m_health = 200;
}

static int i = 0;
static int prevleft_right = 0;
static int prevfront_back = 0;

void Player::update_player(const float deltatime)
{
	if (m_health <= 0)
		return;

	float speed_scalar = 1.0f;
	int left_right = -1;
	int front_back = -1;
	glm::vec3 dir(0);



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		speed_scalar = 1.5f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dir += glm::vec3(0, -1, 0);

		front_back = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dir += glm::vec3(0, 1, 0);

		front_back = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dir += glm::vec3(-1, 0, 0);

		left_right = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dir += glm::vec3(1, 0, 0);

		left_right = 1;
	}


	if (dir != glm::vec3{ 0,0,0 }) //um undefiniertes verhalten zu verhindern und zur optimierung
	{
		dir = normalize(dir);
		dir *= 300 * speed_scalar * deltatime;
		m_pos += dir;
		
		speed = dir; 
		cell_pos = (glm::vec3{ m_pos.x / 135.0f,m_pos.y / 135.0f,m_pos.z });
		if (prev_pos != cell_pos)
		{
			prev_pos = cell_pos;
			EnemyManager::set_player_moving(true);
		}

		i++;
		if (i == 1000)
			i = 0;
		if (front_back != -1)
			prevfront_back = front_back;
		if (left_right != -1)
			prevleft_right = left_right;

		if (i % 20 < 10)
		{
			m_sprite.setTexture(m_textures[prevfront_back][prevleft_right][1]);
		}
		else
		{
			m_sprite.setTexture(m_textures[prevfront_back][prevleft_right][2]);
		}
	}
	else
	{
		m_sprite.setTexture(m_textures[prevfront_back][prevleft_right][0]);
	}
	m_sprite.setPosition(m_pos.x, m_pos.y);
	sf::Listener::setPosition(m_pos.x /135.0f, m_pos.y / 135.0f, 0.f);

	m_hitbox = m_pos + glm::vec3{ 35,117,0 };



}
float condt = 0.0f;
float cooldown = 0.25f;
void Player::shoot(float deltatime, Sounds& i_sounds, glm::vec3 mouse_pos) const
{
	if (m_health <= 0)
		return;




	condt += deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && condt >= cooldown)
	{
		i_sounds.add_sound("player", 2);

		glm::vec3 bullet_dir = normalize(mouse_pos - m_pos);

		new Projectile(m_pos, bullet_dir, 180, 0.2, 5);
		condt = 0;
	}
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

glm::ivec3 Player::get_movement_speed() const {
	return speed;
}

void Player::set_hp(double i_health)
{
	m_health = i_health;
	if (m_health > 200.0)
		m_health = 200.0;
}

void Player::do_damage_calc()
{
	auto& m_enemys = EnemyManager::get_instance()->get_enemies();

	glm::vec3 player_pos = m_pos;
	glm::vec3 player_hitbox = m_hitbox;


	for (auto& enemy : m_enemys) {
		if (enemy == nullptr)
			continue;
		if (!enemy->is_alive()) {
			continue;
		}



		glm::vec3 enemy_pos = enemy->get_pos();
		glm::vec3 enemy_hitbox = enemy->get_hit_box();
		
		// Check if hitboxes intersect
		const bool collision =  player_pos.x <= enemy_hitbox.x &&
			 player_hitbox.x >= enemy_pos.x &&
			 player_pos.y <= enemy_hitbox.y &&
			 player_hitbox.y >= enemy_pos.y;
		if (collision) {
			this->take_damage(enemy->get_damage());
		}
	}
}

void Player::take_damage(const double damage)
{
	m_health -= damage;
	if (m_health < 0)
		m_health = 0;
	else if (m_health > 200)
		m_health = 200;
}
