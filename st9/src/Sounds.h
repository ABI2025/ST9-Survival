#pragma once
#include <deque>
#include <map>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <glm/vec2.hpp>
#include <SFML/Audio.hpp>

#include "Utils/Random.h"

class Sounds
{
	std::unordered_map<int, std::string> m_mapping; // Mapped Gruppen ID zu Gruppen Nammen
	std::unordered_map<std::string, float> m_volumes; // Speichert Lautst�rken f�r jede Gruppe
	std::unordered_map<std::string, std::vector<sf::SoundBuffer>> m_buffers; // Speichert Sound Buffers f�r jede ID die positiv ist in deren Gruppe
	//std::unordered_map<std::string, std::list<sf::SoundBuffer>> m_buffers; // Speichert Sound Buffers f�r jede ID die positiv ist in deren Gruppe
	std::unordered_map<std::string, std::vector<std::pair<std::deque<sf::Sound>, bool>>> m_sounds; // Speicher Sounds pro ID mit Priorit�t Per Gruppe

	int m_current_music = -1;
	float m_grace = 1.5f;
	float m_condt = 0.0f;

	void change_music();
	int current_playing_sounds = 0;
public:
	Sounds();
	~Sounds();

	std::vector<float> get_volumes() const;


	//L�dt eine music file spezifiziert in location und erstellt eine neue deque f�r sounds
	void load_buffer(const std::string& location, bool priority, const std::string& group);

	//f�gt eine gruppe hinzu
	void add_group(const std::string& group);

	//f�gt einen sound hinzu und spielt ihn ab
	void add_sound(int group_id, int id);

	//f�gt einen sound hinzu und spielt ihn ab
	void add_sound(const std::string& group_id, int id);

	//f�gt einen sound hinzu und spielt ihn ab an der spezifizierten stelle
	void add_sound(int group_id, int id, glm::vec2 pos);

	//f�gt einen sound hinzu und spielt ihn ab an der spezifizierten stelle
	void add_sound(const std::string& group_id, int id, glm::vec2 pos);

	//checkt ob Hintergrund musik l�uft falls nein spielt es eine ab
	//geht davon aus, dass die Musik gruppe "music" hei�t
	void music(float deltatime);

	//L�scht alle gestoppten Sounds
	void cleanup();

	//l�scht alles sounds aber nicht buffer
	void delete_sounds();

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

