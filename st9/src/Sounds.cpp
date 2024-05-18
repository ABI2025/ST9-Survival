// ReSharper disable CppTooWideScopeInitStatement
#include "Sounds.h"
#include <ranges>
#include "Utils/Log.h"

Sounds::Sounds()
{
	m_mapping[-1] = "allgemein";
	m_volumes[m_mapping[-1]] = 1.0f;
	//sf::Listener::setDirection(1.f, 0.f, 0.f);
	//sf::Listener::setUpVector(1.f, 1.f, 0.f);
}

Sounds::~Sounds()
{
}

void Sounds::add_sound(int group_id, int id)
{
	// Check if the group ID is valid and mapped
	if (!m_mapping.contains(group_id))
		return;

	const std::string& group_id_string = m_mapping[group_id];

	// Check if the group has associated sounds and buffers
	if (!m_sounds.contains(group_id_string) || !m_buffers.contains(group_id_string))
		return;

	// Check if the sound ID is within the valid range
	if (id < 0 || id >= m_buffers[group_id_string].size())
		return;

	std::deque<sf::Sound>& current_sounds = m_sounds[group_id_string][id].first;
	const bool has_priority = m_sounds[group_id_string][id].second;
	const float allgemeiner_volume = m_volumes[m_mapping[-1]];
	const float group_volume = m_volumes[group_id_string];
	
	// If no priority or sound list is empty (with priority), add and play the sound
	if (!has_priority || (current_sounds.empty() && has_priority))
	{
		const sf::SoundBuffer& sound_buffer = m_buffers[group_id_string][id];
		current_sounds.emplace_back(sound_buffer);
		sf::Sound& current_sound = current_sounds.back();
		current_sound.play();
		current_sound.setVolume(allgemeiner_volume * group_volume * 100);
	}
}

void Sounds::add_sound(const std::string& group_id, const int id)
{
	// Check if the group has associated sounds and buffers
	if (!m_sounds.contains(group_id) || !m_buffers.contains(group_id))
		return;

	// Check if the sound ID is within the valid range
	if (id < 0 || id >= m_buffers[group_id].size())
		return;

	std::deque<sf::Sound>& current_sounds = m_sounds[group_id][id].first;
	const bool has_priority = m_sounds[group_id][id].second;
	const float allgemeiner_volume = m_volumes[m_mapping[-1]];
	const float group_volume = m_volumes[group_id];

	// If no priority or sound list is empty (with priority), add and play the sound
	if (!has_priority || (current_sounds.empty() && has_priority))
	{
		const sf::SoundBuffer& sound_buffer = m_buffers[group_id][id];
		current_sounds.emplace_back(sound_buffer);
		sf::Sound& current_sound = current_sounds.back();
		current_sound.play();
		current_sound.setVolume(allgemeiner_volume * group_volume * 100);
	}
}

void Sounds::add_sound(int group_id, int id, glm::vec2 pos)
{
	// Check if the group ID is valid and mapped
	if (!m_mapping.contains(group_id)) 
		return;

	const std::string& group_id_string = m_mapping[group_id];

	// Check if the group has associated sounds and buffers
	if (!m_sounds.contains(group_id_string) || !m_buffers.contains(group_id_string))
		return;

	// Check if the sound ID is within the valid range
	if (id < 0 || id >= m_buffers[group_id_string].size()) 
		return;

	std::deque<sf::Sound>& current_sounds = m_sounds[group_id_string][id].first;
	const bool has_priority = m_sounds[group_id_string][id].second;
	const float allgemeiner_volume = m_volumes[m_mapping[-1]];
	const float group_volume = m_volumes[group_id_string];

	// If no priority or sound list is empty (with priority), add and play the sound
	if (!has_priority || (current_sounds.empty() && has_priority))
	{
		const sf::SoundBuffer& sound_buffer = m_buffers[group_id_string][id];
		current_sounds.emplace_back(sound_buffer);
		sf::Sound& current_sound = current_sounds.back();
		current_sound.play();
		current_sound.setVolume(allgemeiner_volume * group_volume * 100);
		current_sound.setPosition(pos.x, pos.y, 0.0f);
		current_sound.setRelativeToListener(false);
		current_sound.setMinDistance(135.f);
		current_sound.setAttenuation(1000.f);
	}
}


void Sounds::add_sound(const std::string& group_id, int id, glm::vec2 pos)
{

	// Check if the group has associated sounds and buffers
	if (!m_sounds.contains(group_id) || !m_buffers.contains(group_id))
		return;

	// Check if the sound ID is within the valid range
	if (id < 0 || id >= m_buffers[group_id].size())
		return;

	std::deque<sf::Sound>& current_sounds = m_sounds[group_id][id].first;
	const bool has_priority = m_sounds[group_id][id].second;
	const float allgemeiner_volume = m_volumes[m_mapping[-1]];
	const float group_volume = m_volumes[group_id];

	// If no priority or sound list is empty (with priority), add and play the sound
	if (!has_priority || (current_sounds.empty() && has_priority))
	{
		const sf::SoundBuffer& sound_buffer = m_buffers[group_id][id];
		current_sounds.emplace_back(sound_buffer);
		sf::Sound& current_sound = current_sounds.back();
		current_sound.play();
		current_sound.setVolume(allgemeiner_volume * group_volume * 100);
		current_sound.setPosition(pos.x /135.f, pos.y/135.f, 0.0f);
		current_sound.setRelativeToListener(false);
		current_sound.setMinDistance(1.f);
		current_sound.setAttenuation(100.f);
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

void Sounds::load_buffer(const std::string& location, bool priority, const std::string& group)
{
	sf::SoundBuffer temp_buffer;
	temp_buffer.loadFromFile(location);
	m_buffers[group].push_back(temp_buffer);
	std::deque<sf::Sound> temp_deque;
	m_sounds[group].emplace_back(temp_deque, priority);

}

void Sounds::add_group(const std::string& group)
{
	m_buffers.insert({ group, {} });
	m_sounds.insert({ group, {} });
	m_mapping[m_sounds.size() - 1] = group;
	m_volumes.insert({ group ,1.0f });

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
	// Ensure the volume is within the valid range [0.0, 100.0]
	if (volume < 0.0f || volume > 100.0f) return;

	// Check if the ID exists in the mapping
	if (!m_mapping.contains(id)) return;

	// Get the group ID string from the mapping
	const std::string& group_id_string = m_mapping[id];
	const float normalized_volume = volume / 100.0f;
	m_volumes[group_id_string] = normalized_volume;

	// If the ID is -1, update the global volume and apply it to all sounds
	if (id == -1)
	{
		// Update volume for all sound groups
		for (const auto& group_name : m_mapping | std::views::values)
		{
			// Skip if the group name does not have sounds
			if (!m_sounds.contains(group_name)) continue;

			// Update the volume for each sound in the group
			for (auto& sounds : m_sounds[group_name] | std::views::keys)
			{
				for (sf::Sound& sound : sounds)
				{
					sound.setVolume(normalized_volume * m_volumes[group_name] * 100.0f);
				}
			}
		}
	}
	else
	{
		// Update the volume for the specific sound group
		if (m_volumes.contains(group_id_string))
		{
			const float global_volume = m_volumes[m_mapping[-1]];

			// Update the volume for each sound in the specific group
			for (auto& sounds : m_sounds[group_id_string] | std::views::keys)
			{
				for (sf::Sound& sound : sounds)
				{
					sound.setVolume(global_volume * normalized_volume * 100.0f);
				}
			}
		}
	}
}



//void Sounds::set_volume(float volume, int id)
//{
//	if (volume >= 0.0f && volume <= 100.0f)
//	{
//		if (!m_mapping.contains(id))
//			return;
//		const std::string group_id_string = m_mapping[id];
//		if (id == -1)
//		{
//			m_volumes[group_id_string] = volume / 100;
//			for (uint32_t i = 0; i < m_sounds.size(); ++i)
//			{
//				for (std::deque<sf::Sound>& sounds : m_sounds[m_mapping[i]] | std::views::keys)
//				{
//					for (sf::Sound& sound : sounds)
//					{
//						sound.setVolume(m_volumes[group_id_string] * m_volumes[m_mapping[i]] * 100);
//					}
//				}
//			}
//		}
//		else
//		{
//			if (m_volumes.contains(group_id_string))
//			{
//				m_volumes[group_id_string] = volume / 100;
//				const float allgemeiner_volume = m_volumes[m_mapping[-1]];
//				for (std::deque<sf::Sound>& sounds : m_sounds[group_id_string] | std::views::keys)
//				{
//					for (sf::Sound& sound : sounds)
//					{
//						sound.setVolume(allgemeiner_volume * m_volumes[group_id_string] * 100);
//					}
//				}
//
//			}
//		}
//	}
//}
