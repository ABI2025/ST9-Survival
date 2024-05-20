#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "entities/entity/Entity.h"



class ProjectileTexture
{
	inline static ProjectileTexture* s_instance;
public:
	sf::Texture texture;
	ProjectileTexture();
	static ProjectileTexture* get_instance();

	static void delete_instance();
};

class Projectile : public Entity {
private:
	glm::vec3 m_speed;
	int m_lifetime;
	double m_damage;
	int m_penetration; // das projectil soll verschwinden wenn das 0 erreicht
	thread_local inline static std::vector<Projectile*> s_projectiles;
	sf::Sprite sprite;
public:
	Projectile(glm::vec3 pos, glm::vec3 speed, int lifetime, double damage, int penetration);
	~Projectile() override;
	int get_penetration() const;
	double get_damage() const;
	void decrease_penetration(int);
	void update(float deltatime);
	static void remove_projectile(Projectile* projectile);
	static void update_all(float deltatime);
	static void draw_all_projectiles(sf::RenderTarget& target, const sf::RenderStates& states = sf::RenderStates::Default);
	static std::vector<Projectile*>& get_projectiles();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	static void clean_up();
};
