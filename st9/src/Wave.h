#pragma once
#include <deque>

#include "Utils/Utils.h"
#include "entities/EnemyManager.h"






enum Wave_kind
{
	Wave_Endless,
	Wave_Normal
};
typedef int Wavekind;





class Wave
{
	Wavekind m_wavekind{Wave_Normal};
	float m_cooldown_before_start{ 5.0f};
	float m_num_enemies{};
	float condt{0};
	bool spawned = false;
	int m_enemy_type;
	
public:
	explicit Wave(float num_enemies,float cooldown_before_start = 5.0f , int i_enemy_type = 0);
	void spawn_wave(EnemyManager* ma,float dt);
	bool was_spawned() const { return spawned; }
	float get_cooldown_before_start() const{ return m_cooldown_before_start; }
	inline static int wave_counter = 0;
};


class WaveManager
{
std::deque<std::shared_ptr<Wave>> waves;
std::shared_ptr<Wave> current_wave;
bool done = false;
public:
	WaveManager();
	void spawnening(EnemyManager* ma,float dt);
};
