// ReSharper disable CppTooWideScopeInitStatement
#include "Sounds.h"
#include <ranges>
#include "Utils/Log.h"

Sounds::Sounds()
{
	m_mapping[-1] = "allgemein";
	m_volumes[m_mapping[- 1]] = 1.0f;
}

Sounds::~Sounds()
{
}

void Sounds::add_sound(int group_id,int id)
{
	if (m_mapping.contains(id))
	{
		std::string group_id_string = m_mapping[group_id];
		if (!(id < 0 || id >= m_buffers[m_mapping[group_id]].size())) 
		{
			if (!m_sounds[m_mapping[group_id]][id].second)
			{
				m_sounds[m_mapping[group_id]][id].first.emplace_back(m_buffers[group_id_string][id]);
				m_sounds[m_mapping[group_id]][id].first.back().play();
				m_sounds[m_mapping[group_id]][id].first.back().setVolume(m_volumes[group_id_string] * m_volumes[group_id_string] * 100);
			}
			else
			{
				if (m_sounds[m_mapping[group_id]][id].first.empty())
				{
					m_sounds[m_mapping[group_id]][id].first.emplace_back(m_buffers[group_id_string][id]);
					m_sounds[m_mapping[group_id]][id].first.back().play();
					m_sounds[m_mapping[group_id]][id].first.back().setVolume(m_volumes[group_id_string] * m_volumes[group_id_string] * 100);
				}

			}
		}
	}
}

void Sounds::add_sound(const std::string& group_id, const int id)
{

	if (m_sounds.contains(group_id) && m_buffers.contains(group_id))
	{
		if (!(id < 0 || id >= m_buffers[group_id].size()))
		{
			if (!m_sounds[group_id][id].second)
			{
				m_sounds[group_id][id].first.emplace_back(m_buffers[group_id][id]);
				m_sounds[group_id][id].first.back().play();
				m_sounds[group_id][id].first.back().setVolume(m_volumes[group_id] * m_volumes[group_id] * 100);
			}
			else
			{
				if (m_sounds[group_id][id].first.empty())
				{
					m_sounds[group_id][id].first.emplace_back(m_buffers[group_id][id]);
					m_sounds[group_id][id].first.back().play();
					m_sounds[group_id][id].first.back().setVolume(m_volumes[group_id] *m_volumes[group_id] * 100);
				}

			}
		}
	}
}

void Sounds::cleanup(const bool priority_ignorieren)
{
	for (auto& all_sounds : m_sounds | std::views::values) 
	{
		for (auto& [sounds, priority] : all_sounds)
		{
			if (priority && !priority_ignorieren)
			{
				int i = 0;
				for (auto& sound : sounds)
				{
					if (sound.getStatus() == sf::SoundSource::Stopped)
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
}

void Sounds::load_buffer(const std::string& location, bool priority,const std::string& group)
{
	sf::SoundBuffer temp_buffer;
	temp_buffer.loadFromFile(location);
	m_buffers[group].push_back(temp_buffer);
	std::deque<sf::Sound> temp_deque;
	m_sounds[group].emplace_back(temp_deque,priority);
	
}

void Sounds::add_group(const std::string& group)
{
	m_buffers.insert({ group, {} });
	m_sounds.insert({ group, {} });
	m_mapping[m_sounds.size() - 1] = group;
	m_volumes.insert({group ,1.0f });
	
}

void Sounds::pause_all(bool priority_ignorieren)
{
	for (auto& all_sounds : m_sounds | std::views::values)
	{
		for (auto& [sounds, priority] : all_sounds)
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
}

void Sounds::play_all()
{
	for (auto& all_sounds : m_sounds | std::views::values)
	{
		for (auto& sounds : all_sounds | std::views::keys)
		{
			for (auto& sound : sounds)
			{
				if (sound.getStatus() != sf::SoundSource::Playing && sound.getStatus() != sf::SoundSource::Stopped)
				{
					sound.play();
				}
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
	if (volume >= 0.0f && volume <= 100.0f) 
	{
		if (!m_mapping.contains(id))
			return;
		std::string group_id_string = m_mapping[id];
		if (id == -1)
		{
			m_volumes[group_id_string] = volume/100;
			for (uint32_t i = 0; i < m_sounds.size(); ++i)
			{
				for (std::deque<sf::Sound>& sounds : m_sounds[m_mapping[i]] | std::views::keys)
				{
					for (sf::Sound& sound : sounds)
					{
						sound.setVolume(m_volumes[group_id_string] * m_volumes[m_mapping[i]] * 100);
					}
				}
			}
		}
		else
		{
			if (m_volumes.contains(group_id_string))
			{
				m_volumes[group_id_string] = volume / 100;
				
				for (std::deque<sf::Sound>& sounds : m_sounds[group_id_string] | std::views::keys)
				{
					for (sf::Sound& sound : sounds)
					{
						sound.setVolume(m_volumes[m_mapping[-1]] * m_volumes[group_id_string] * 100);
					}
				}
				
			}
		}
	}
}
