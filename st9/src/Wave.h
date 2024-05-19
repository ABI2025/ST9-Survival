#pragma once
#include <deque>
#include <vector>

#include "Utils/Random.h"
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
public:
	explicit Wave(float num_enemies,float cooldown_before_start = 5.0f):m_cooldown_before_start(cooldown_before_start),m_num_enemies(num_enemies)
	{
		
	}
	void spawn_wave(EnemyManager* ma,float dt);
	bool was_spawned() { return spawned; }
};


class WaveManager
{
std::deque<std::shared_ptr<Wave>> waves;
std::shared_ptr<Wave> current_wave;
bool done = false;
public:
	WaveManager()
	{
		waves.push_back(std::make_shared<Wave>(Wave{ 10,10 }));
		current_wave = waves.front();
		waves.pop_front();
		waves.push_back(std::make_shared<Wave>(Wave{10,10 }));
		waves.push_back(std::make_shared<Wave>(Wave{10,10 }));
		waves.push_back(std::make_shared<Wave>(Wave{10,5 }));
		waves.push_back(std::make_shared<Wave>(Wave{10,2 }));
		waves.push_back(std::make_shared<Wave>(Wave{10,0.5 }));
		waves.push_back(std::make_shared<Wave>(Wave{10,5 }));
		waves.push_back(std::make_shared<Wave>(Wave{10,0.5 }));
		waves.push_back(std::make_shared<Wave>(Wave{100,0 }));
		waves.push_back(std::make_shared<Wave>(Wave{100,20 }));
		waves.push_back(std::make_shared<Wave>(Wave{1000,20 }));
	}
	void spawnening(EnemyManager* ma,float dt)
	{
		if (done) 
		{
			current_wave->spawn_wave(ma, dt);
			if(current_wave->was_spawned())
			{
				current_wave.reset();
				current_wave = std::make_shared<Wave>(Wave{ Utils::Random::Float(100,1000),Utils::Random::Float(10,30) });
				LOG_INFO("boah einfach crazy");
			}
			return;
		}

		current_wave->spawn_wave(ma, dt);
		if(current_wave->was_spawned())
		{
			current_wave.reset();
			current_wave = waves.front();
			waves.pop_front();
			if (waves.empty())
			{
				LOG_INFO("done");
				//current_wave = std::make_shared<Wave>(Wave{ Utils::Random::Float(100,200),Utils::Random::Float(10,20) });
				done = true;
			}
		}
	}

};
