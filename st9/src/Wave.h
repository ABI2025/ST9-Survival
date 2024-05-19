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
public:
	explicit Wave(float num_enemies,float cooldown_before_start = 5.0f):m_cooldown_before_start(cooldown_before_start),m_num_enemies(num_enemies)
	{
		
	}
	void spawn_wave(EnemyManager* ma,float dt);
};


class WaveManager
{
std::deque<std::shared_ptr<Wave>> waves;
std::shared_ptr<Wave> current_wave;
public:
	WaveManager()
	{
		waves.push_back(std::make_shared<Wave>(10,20));
		waves.push_back(std::make_shared<Wave>(10,10));
		waves.push_back(std::make_shared<Wave>(10,5));
		waves.push_back(std::make_shared<Wave>(10,5));
		waves.push_back(std::make_shared<Wave>(10,2));
		waves.push_back(std::make_shared<Wave>(10,0.5));
		waves.push_back(std::make_shared<Wave>(10,5));
		waves.push_back(std::make_shared<Wave>(10,0.5));
		waves.push_back(std::make_shared<Wave>(100,0));
		waves.push_back(std::make_shared<Wave>(100,20));
		waves.push_back(std::make_shared<Wave>(100,20));
	}


};
