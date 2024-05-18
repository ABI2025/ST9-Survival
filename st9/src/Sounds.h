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
	std::unordered_map<std::string, float> m_volumes; // Speichert Lautst�rken f�r jede Gruppe
	std::unordered_map<std::string, std::vector<sf::SoundBuffer>> m_buffers; // Speichert Sound Buffers f�r jede ID die positiv ist in deren Gruppe
	std::unordered_map<std::string, std::vector<std::pair<std::deque<sf::Sound>, bool>>> m_sounds; // Speicher Sounds pro ID mit Priorit�t Per Gruppe

public:
	Sounds();
	~Sounds();
	//f�gt einen sound hinzu und spielt ihn ab
	void add_sound(int group_id, int id);

	//f�gt einen sound hinzu und spielt ihn ab
	void add_sound(const std::string& group_id, int id);

	//f�gt einen sound hinzu und spielt ihn ab an der spezifizierten stelle
	void add_sound(int group_id, int id, glm::vec2 pos);

	//f�gt einen sound hinzu und spielt ihn ab an der spezifizierten stelle
	void add_sound(const std::string& group_id, int id, glm::vec2 pos);

	//L�scht alle gestoppten Sounds
	void cleanup(bool priority_ignorieren);

	//L�dt eine music file spezifiziert in location und erstellt eine neue deque f�r sounds
	void load_buffer(const std::string& location, bool priority, const std::string& group);

	//f�gt eine gruppe hinzu
	void add_group(const std::string& group);

	//pausiert alle nicht gestoppten lieder
	void pause_all(bool priority_ignorieren);

	//spielt alle sounds ab die nicht gerade abgespielt werden oder gestoppt sind
	void play_all();

	//l�scht alle buffer und sounds
	void clear_all();

	// setzt die lautst�rke von allen sounds der entsprechenden id auf volume
	// wenn id gleich -1 ist wird die gesamt laust�rke ver�ndert
	void set_volume(float volume, int id);
};

