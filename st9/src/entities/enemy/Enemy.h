#pragma once
#include "entities/entity/Entity.h"
#include "Utils/Utils.h"
enum enemy_type {
	Default_Enemy,
	Red_Enemy,
	Blue_Enemy,
	Gold_Enemy,
	Black_Enemy
};
class Enemy :
	public Entity
{

public:

	double get_damage() const;
	Enemy();
	void die();
	void attack();
	void update(float deltatime) override;
	bool is_alive() const;
	Utils::Priority get_priority() const;
private:
	enemy_type m_enemy_type = Default_Enemy;
	std::vector<glm::vec3> m_movements;
	Utils::Priority m_priority;
	size_t prev_size{};
	double m_damage;
	double m_id = 0;
	bool can_be_removed = false;
	bool currently_dying = false;
	double m_speed;
	friend class EnemyManager;
};

