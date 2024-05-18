#pragma once
#include <deque>
#include <map>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <glm/vec2.hpp>
#include <SFML/Audio.hpp>

class Sounds
{
	std::unordered_map<int, std::string> m_mapping; // Mapped Gruppen ID zu Gruppen Nammen
	std::unordered_map<std::string, float> m_volumes; // Speichert Lautstärken für jede Gruppe
	std::unordered_map<std::string, std::vector<sf::SoundBuffer>> m_buffers; // Speichert Sound Buffers für jede ID die positiv ist in deren Gruppe
	std::unordered_map<std::string, std::vector<std::pair<std::deque<sf::Sound>, bool>>> m_sounds; // Speicher Sounds pro ID mit Priorität Per Gruppe

public:
	Sounds();
	~Sounds();
	//fügt einen sound hinzu und spielt ihn ab
	void add_sound(int group_id, int id);

	//fügt einen sound hinzu und spielt ihn ab
	void add_sound(const std::string& group_id, int id);

	//fügt einen sound hinzu und spielt ihn ab an der spezifizierten stelle
	void add_sound(int group_id, int id, glm::vec2 pos);

	//fügt einen sound hinzu und spielt ihn ab an der spezifizierten stelle
	void add_sound(const std::string& group_id, int id, glm::vec2 pos);

	//Löscht alle gestoppten Sounds
	void cleanup(bool priority_ignorieren);

	//Lädt eine music file spezifiziert in location und erstellt eine neue deque für sounds
	void load_buffer(const std::string& location, bool priority, const std::string& group);

	//fügt eine gruppe hinzu
	void add_group(const std::string& group);

	//pausiert alle nicht gestoppten lieder
	void pause_all(bool priority_ignorieren);

	//spielt alle sounds ab die nicht gerade abgespielt werden oder gestoppt sind
	void play_all();

	//löscht alle buffer und sounds
	void clear_all();

	// setzt die lautstärke von allen sounds der entsprechenden id auf volume
	// wenn id gleich -1 ist wird die gesamt laustärke verändert
	void set_volume(float volume, int id);
};

