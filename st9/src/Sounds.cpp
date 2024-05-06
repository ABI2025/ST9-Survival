#include "Sounds.h"

#include "Utils/Log.h"

Sounds::~Sounds()
{
}

void Sounds::add_sound(int id)
{
	if (!(id < 0 || id >= m_sounds.size())) 
	{
		if (!m_sounds[id].second)
		{
			m_sounds[id].first.emplace_back(m_buffers[id]);
			m_sounds[id].first.back().play();
		}
		else
		{
			if(m_sounds[id].first.empty())
			{
				m_sounds[id].first.emplace_back(m_buffers[id]);
				m_sounds[id].first.back().play();
			}

		}
	}
}

void Sounds::cleanup(bool priority_ignorieren)
{
	for (auto& [sounds, priority] : m_sounds)
	{
		if(priority && !priority_ignorieren)
		{
			int i = 0;
			for(auto& sound : sounds)
			{
				if(sound.getStatus() == sf::SoundSource::Stopped)
					sound.play();
				i++;
			}
			if (i > 1)
				LOG_CRITICAL("hilfe");
		}
		if (!priority || priority_ignorieren) 
		{
			for (auto it = sounds.begin(); it != sounds.end();)
			{
				if (it->getStatus() == sf::SoundSource::Stopped)
				{
					it = sounds.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
	}
}

void Sounds::load_buffer(const std::string& location, bool priority)
{
	sf::SoundBuffer temp_buffer;
	temp_buffer.loadFromFile(location);
	m_buffers.push_back(temp_buffer);
	std::deque<sf::Sound> temp_deque;
	m_sounds.emplace_back(temp_deque, priority);
}

void Sounds::pause_all(bool priority_ignorieren)
{
	for (auto& [sounds, priority]: m_sounds)
	{
		if (!priority || priority_ignorieren) 
		{
			for (auto& sound : sounds)
			{
				if (sound.getStatus() != sf::SoundSource::Stopped)
				{
					sound.pause();
				}
			}
		}
	}
}

void Sounds::play_all()
{
	for (auto& [sounds, priority] : m_sounds)
	{
		for (auto& sound : sounds)
		{
			if (sound.getStatus() != sf::SoundSource::Playing)
			{
				sound.play();
			}
		}
	}
}

void Sounds::clear_all()
{
	m_sounds.clear();
	m_buffers.clear();
}
