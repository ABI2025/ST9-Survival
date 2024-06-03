#include "Wave.h"

constexpr int BACKGROUND_HEIGHT = 135;
constexpr int BACKGROUND_WIDTH = 135;

constexpr int height = 22;
constexpr int width = 41;


Wave::Wave(const float num_enemies, const float cooldown_before_start, const int i_enemy_type):m_cooldown_before_start(cooldown_before_start),m_num_enemies(num_enemies),m_enemy_type(i_enemy_type)
{
		
}

void Wave::spawn_wave(EnemyManager* ma, const float dt)
{
	condt += dt;
	if (condt >= m_cooldown_before_start)
	{
		wave_counter++;
		for (int i = 0; i < m_num_enemies; i++)
		{
			switch (const int dir = static_cast<signed>(Utils::Random::UInt(0, 3)))
			{
			case 0://oben
				ma->add_enemy(glm::vec3(Utils::Random::UInt(0, width * BACKGROUND_WIDTH - BACKGROUND_WIDTH), 0, 0),
					static_cast<Utils::Priority>(Utils::Random::UInt(0, 2)), m_enemy_type);
				break;
			case 1://links
				ma->add_enemy(glm::vec3(0, Utils::Random::UInt(0, height * BACKGROUND_HEIGHT - BACKGROUND_WIDTH), 0),
					static_cast<Utils::Priority>(Utils::Random::UInt(0, 2)), m_enemy_type);
				break;
			case 2://unten
				ma->add_enemy(glm::vec3(Utils::Random::UInt(0, width * BACKGROUND_WIDTH - BACKGROUND_WIDTH), (height - 1) * BACKGROUND_HEIGHT, 0),
					static_cast<Utils::Priority>(Utils::Random::UInt(0, 2)), m_enemy_type);
				break;
			case 3://rechts
				ma->add_enemy(glm::vec3((width - 1) * BACKGROUND_WIDTH, Utils::Random::UInt(0, height * BACKGROUND_HEIGHT - BACKGROUND_WIDTH), 0),
					static_cast<Utils::Priority>(Utils::Random::UInt(0, 2)), m_enemy_type);
				break;
			default:
				break;
			}
		}
		spawned = true;
	}
}

WaveManager::WaveManager()
{
	waves.push_back(std::make_shared<Wave>(Wave{ 10,10 }));
	current_wave = waves.front();
	waves.pop_front();
	waves.push_back(std::make_shared<Wave>(Wave{10,10 }));

	waves.push_back(std::make_shared<Wave>(Wave{5,15}));
	waves.push_back(std::make_shared<Wave>(Wave{15,1 ,1 }));

	waves.push_back(std::make_shared<Wave>(Wave{25,10 }));

	waves.push_back(std::make_shared<Wave>(Wave{10,10,2 }));
	waves.push_back(std::make_shared<Wave>(Wave{20,0}));

	waves.push_back(std::make_shared<Wave>(Wave{10,13 ,2 }));
	waves.push_back(std::make_shared<Wave>(Wave{20,4 ,1 }));

	waves.push_back(std::make_shared<Wave>(Wave{ 10,12 ,4}));
	waves.push_back(std::make_shared<Wave>(Wave{70,3 }));
		


	waves.push_back(std::make_shared<Wave>(Wave{30,22 ,4}));
	waves.push_back(std::make_shared<Wave>(Wave{50,2 ,2}));

	waves.push_back(std::make_shared<Wave>(Wave{160,15 }));
	waves.push_back(std::make_shared<Wave>(Wave{240,22 }));
	waves.push_back(std::make_shared<Wave>(Wave{100,22,4 }));
	waves.push_back(std::make_shared<Wave>(Wave{400,22,1}));
	waves.push_back(std::make_shared<Wave>(Wave{300,22,2 }));
	waves.push_back(std::make_shared<Wave>(Wave{100,3,1 }));
}

void WaveManager::spawnening(EnemyManager* ma, const float dt)
{
		
	if (done) 
	{
		waves.push_back(std::make_shared<Wave>(Wave{ Wave::wave_counter * 3.f ,30.f , 3}));
		waves.push_back(std::make_shared<Wave>(Wave{ Wave::wave_counter * 5.f ,0.f , 4}));
		waves.push_back(std::make_shared<Wave>(Wave{ Wave::wave_counter * 2.f ,0.f , 1}));
		done = false;
		//LOG_INFO("boah einfach crazy");
			
	}

	current_wave->spawn_wave(ma, dt);
	if(current_wave->was_spawned())
	{
		current_wave.reset();
		current_wave = waves.front();
		waves.pop_front();
		if (waves.empty())
		{
			//LOG_INFO("done");
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
