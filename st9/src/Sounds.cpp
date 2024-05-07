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
			m_sounds[id].first.back().setVolume(volumes[-1] * volumes[id] * 100);
		}
		else
		{
			if(m_sounds[id].first.empty())
			{
				m_sounds[id].first.emplace_back(m_buffers[id]);
				m_sounds[id].first.back().play();
				m_sounds[id].first.back().setVolume(volumes[-1]*volumes[id]*100);
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
	volumes.insert({m_sounds.size() ,1.0f});
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
	for (auto& sounds : m_sounds | std::views::keys)
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

void Sounds::set_volume(float volume, int id)
{
	if (volume > 0 && volume <= 100) 
	{
		if (id == -1)
		{
			volumes[-1] = volume/100;
			for (int i = 0; i < m_sounds.size(); ++i)
			{
				for (auto& sound : m_sounds[i].first)
				{
					sound.setVolume(volumes[-1] * volumes[i] * 100);
				}
			}

		}
		else
		{
			for(int i = 0; i < m_sounds.size(); ++i)
			{
				if(i == id)
				{
					volumes[i] = volume/100;
					for(auto& sound :m_sounds[i].first)
					{
						sound.setVolume(volumes[-1] * volumes[i] * 100);
					}
				}
			}
		}

	}
}
