// ReSharper disable CppTooWideScopeInitStatement

#include "projektil.h"

#include "Optionen.h"
#include "Utils/Log.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
ProjectileTexture::ProjectileTexture()
{
	texture.loadFromFile("resources/images/Projektil.png");

}

ProjectileTexture* ProjectileTexture::get_instance()
{
	if (!s_instance)
	{
		s_instance = new ProjectileTexture;
	}
	return s_instance;
}

void ProjectileTexture::delete_instance()
{
	delete s_instance;
	s_instance = nullptr;
}

Projectile::Projectile(glm::vec3 pos, glm::vec3 speed, int lifetime, double damage, int penetration)
	: Entity(), m_speed(speed), m_lifetime(lifetime), m_damage(damage), m_penetration(penetration)
{
	m_pos = pos;
	s_projectiles.push_back(this);

	sprite.setTexture(ProjectileTexture::get_instance()->texture);
	sprite.setOrigin(4.0f, 12.5f);
	sprite.setPosition(m_pos.x + 4.0f, m_pos.y + 12.5f);
	// Calculate the angle for rotation
	float angle = std::atan2(speed.y, speed.x) * 180.0f / M_PI; //Herr John wäre stolz
	angle += 90;

	sprite.setRotation(angle);
}

Projectile::~Projectile() = default;

void Projectile::update(const float deltatime)
{
	const glm::vec3 new_pos = (m_pos + m_speed * 600.0f * deltatime);
	m_pos = new_pos;
	m_lifetime--;
	m_hitbox = m_pos + glm::vec3{ 8,25,20 };
	sprite.setPosition(m_pos.x + 4.0f, m_pos.y + 12.5f);
	if (Optionen::get_instance()->get_should_rotate())
		sprite.rotate(3600.f * deltatime);
	else
		sprite.setRotation(std::atan2(m_speed.y, m_speed.x) * 180.0f / M_PI + 90);
}

void Projectile::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	if (m_lifetime > 0)
	{
		//sf::RectangleShape projectile_shape(sf::Vector2f(20, 20));
		//projectile_shape.setFillColor(sf::Color::Red);
		//projectile_shape.setPosition(get_pos().x, get_pos().y);
		target.draw(sprite, states);
	}
}

void Projectile::clean_up()
{
	std::erase_if(s_projectiles, [](const Projectile* p)
		{
			const bool should_remove = p->m_lifetime <= 0;
			//if (should_remove)
			//{
			//	delete p;
			//}
			return should_remove;
		});
}

void Projectile::update_all(const float deltatime)
{
	for (Projectile* p : s_projectiles)
	{
		p->update(deltatime);
	}
	clean_up();
}

void Projectile::draw_all_projectiles(sf::RenderTarget& target, const sf::RenderStates& states) //von Elias (Seinem ego gehts gut)
{
	for (const Projectile* proj : s_projectiles)
	{
		if (proj != nullptr && proj->m_lifetime > 0)
		{
			proj->draw(target, states);
		}
	}
}

void Projectile::remove_projectile(Projectile* projectile)
{
	const auto it = std::ranges::find(s_projectiles, projectile);
	if (it != s_projectiles.end())
	{
		/*delete *it;*/
		s_projectiles.erase(it);
	}
}

void Projectile::decrease_penetration(const int prenetation_decrease)
{
	m_penetration -= prenetation_decrease;
}

double Projectile::get_damage() const
{
	return m_damage;
}
int Projectile::get_penetration() const
{
	return m_penetration;
}
std::vector<Projectile*>& Projectile::get_projectiles()
{
	return s_projectiles;
}
