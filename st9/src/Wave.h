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
	int m_enemy_type;
	
public:
	explicit Wave(float num_enemies,float cooldown_before_start = 5.0f , int i_enemy_type = 0):m_cooldown_before_start(cooldown_before_start),m_num_enemies(num_enemies),m_enemy_type(i_enemy_type)
	{
		
	}
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
	WaveManager()
	{
		waves.push_back(std::make_shared<Wave>(Wave{ 10,10 }));
		current_wave = waves.front();
		waves.pop_front();
		waves.push_back(std::make_shared<Wave>(Wave{10,10 }));

		waves.push_back(std::make_shared<Wave>(Wave{5,10}));
		waves.push_back(std::make_shared<Wave>(Wave{15,1 ,1 }));

		waves.push_back(std::make_shared<Wave>(Wave{25,10 }));

		waves.push_back(std::make_shared<Wave>(Wave{10,7,2 }));
		waves.push_back(std::make_shared<Wave>(Wave{20,0}));

		waves.push_back(std::make_shared<Wave>(Wave{10,10 ,2 }));
		waves.push_back(std::make_shared<Wave>(Wave{20,4 ,1 }));

		waves.push_back(std::make_shared<Wave>(Wave{ 10,10 ,4}));
		waves.push_back(std::make_shared<Wave>(Wave{70,3 }));
		


		waves.push_back(std::make_shared<Wave>(Wave{30,20 ,4}));
		waves.push_back(std::make_shared<Wave>(Wave{50,2 ,2}));

		waves.push_back(std::make_shared<Wave>(Wave{160,10 }));
		waves.push_back(std::make_shared<Wave>(Wave{240,20 }));
		waves.push_back(std::make_shared<Wave>(Wave{100,20,4 }));
		waves.push_back(std::make_shared<Wave>(Wave{400,20,1}));
		waves.push_back(std::make_shared<Wave>(Wave{300,20,2 }));
		waves.push_back(std::make_shared<Wave>(Wave{100,3,1 }));
	}
	void spawnening(EnemyManager* ma,float dt)
	{
		
		if (done) 
		{
				waves.push_back(std::make_shared<Wave>(Wave{ Wave::wave_counter * 3.f ,20.f , 3}));
				waves.push_back(std::make_shared<Wave>(Wave{ Wave::wave_counter * 9.f ,0.f , 4}));
				waves.push_back(std::make_shared<Wave>(Wave{ Wave::wave_counter * 2.f ,0.f , 1}));
				done = false;
				LOG_INFO("boah einfach crazy");
			
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
			else
			{
				if(current_wave->get_cooldown_before_start() == 0.f)
				{
					spawnening(ma, 0);
				}

			}
		}
	}

};
