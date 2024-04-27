#include "Projektil.h"
#include <algorithm>
#include "Utils/Log.h"

Projectile::Projectile(glm::vec3 pos, glm::vec3 speed, int lifetime, double damage, int penetration)
	: Entity(), m_speed(speed), m_lifetime(lifetime), m_damage(damage), m_penetration(penetration)
{
	set_pos(pos);
	s_projectiles.push_back(this);
}

Projectile::~Projectile() {}

void Projectile::update()
{
	const glm::vec3 new_pos = get_pos() + m_speed;
	set_pos(new_pos);
	m_lifetime--;
	this->m_hitbox = this->m_pos + glm::vec3{ 20,20,20 };
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_lifetime > 0)
	{
		sf::RectangleShape projectile_shape(sf::Vector2f(20, 20));
		projectile_shape.setFillColor(sf::Color::Red);
		projectile_shape.setPosition(get_pos().x, get_pos().y);
		target.draw(projectile_shape, states);
	}
}

void Projectile::clean_up()
{
	std::erase_if(s_projectiles, [](const Projectile* p)
		{
			const bool should_remove = p->m_lifetime <= 0;
			if (should_remove)
			{
				delete p;
			}
			return should_remove;
		});
}

void Projectile::update_all()
{
	for (Projectile* p : s_projectiles)
	{
		p->update();
	}
	clean_up();
}

void Projectile::draw_all_projectiles(sf::RenderTarget& target, const sf::RenderStates& states) //von Elias (Seinem ego gehts gut)
{
	update_all();
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
		delete* it;
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