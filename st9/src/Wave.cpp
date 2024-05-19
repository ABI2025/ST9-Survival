#include "Wave.h"

constexpr int BACKGROUND_HEIGHT = 135;
constexpr int BACKGROUND_WIDTH = 135;

constexpr int height = 22;
constexpr int width = 41;

void Wave::spawn_wave(EnemyManager* ma,float dt)
{
	condt += dt;
	if (condt >= m_cooldown_before_start)
	{
		for (int i = 0; i < m_num_enemies; i++)
		{
			switch (const int dir = (signed)Utils::Random::UInt(0, 3))
			{
			case 0://oben
				ma->add_enemy(glm::vec3(Utils::Random::UInt(0, width * BACKGROUND_WIDTH - BACKGROUND_WIDTH), 0, 0),
					static_cast<Utils::Priority>(Utils::Random::UInt(0, 2)));
				break;
			case 1://links
				ma->add_enemy(glm::vec3(0, Utils::Random::UInt(0, height * BACKGROUND_HEIGHT - BACKGROUND_WIDTH), 0),
					static_cast<Utils::Priority>(Utils::Random::UInt(0, 2)));
				break;
			case 2://unten
				ma->add_enemy(glm::vec3(Utils::Random::UInt(0, width * BACKGROUND_WIDTH - BACKGROUND_WIDTH), (height - 1) * BACKGROUND_HEIGHT, 0),
					static_cast<Utils::Priority>(Utils::Random::UInt(0, 2)));
				break;
			case 3://rechts
				ma->add_enemy(glm::vec3((width - 1) * BACKGROUND_WIDTH, Utils::Random::UInt(0, height * BACKGROUND_HEIGHT - BACKGROUND_WIDTH), 0),
					static_cast<Utils::Priority>(Utils::Random::UInt(0, 2)));
				break;
			default:
				break;
			}
		}
	}
}
