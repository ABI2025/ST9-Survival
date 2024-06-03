#pragma once
#include <deque>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <SFML/Audio.hpp>

#include "Utils/Random.h"

class Sounds
{
	std::unordered_map<int, std::string> m_mapping; // Mapped Gruppen ID zu Gruppen Nammen
	std::unordered_map<std::string, float> m_volumes; // Speichert Lautstaerken für jede Gruppe
	std::unordered_map<std::string, std::vector<sf::SoundBuffer>> m_buffers; // Speichert Sound Buffers für jede ID die positiv ist in deren Gruppe
	std::unordered_map<std::string, std::vector<std::pair<std::deque<sf::Sound>, bool>>> m_sounds; // Speicher Sounds pro ID mit Prioritaet per Gruppe

	int m_current_music = -1;
	float m_grace = 1.5f;
	float m_condt = 0.0f;

	void change_music();
	int current_playing_sounds = 0;
public:
	Sounds();
	~Sounds();

	std::vector<float> get_volumes() const;


	//Laedt eine music file spezifiziert in location und erstellt eine neue deque fuer sounds
	void load_buffer(const std::string& location, bool priority, const std::string& group);

	//fuegt eine gruppe hinzu
	void add_group(const std::string& group);

	//fuegt einen sound hinzu und spielt ihn ab
	void add_sound(int group_id, int id);

	//fuegt einen sound hinzu und spielt ihn ab
	void add_sound(const std::string& group_id, int id);

	//fuegt einen sound hinzu und spielt ihn ab an der spezifizierten stelle
	void add_sound(int group_id, int id, glm::vec2 pos);

	//fuegt einen sound hinzu und spielt ihn ab an der spezifizierten stelle
	void add_sound(const std::string& group_id, int id, glm::vec2 pos);

	//checkt ob Hintergrund musik laeuft falls nein spielt es eine ab
	//geht davon aus, dass die Musik gruppe "music" heißt
	void music(float deltatime);

	//Loescht alle gestoppten Sounds
	void cleanup();

	//loescht alles sounds aber nicht buffer
	void delete_sounds();

	//pausiert alle nicht gestoppten lieder
	void pause_all(bool priority_ignorieren);

	//spielt alle sounds ab die nicht gerade abgespielt werden oder gestoppt sind
	void play_all();

	//loescht alle buffer und sounds
	void clear_all();

	// setzt die Lautstaerke von allen sounds der entsprechenden id auf volume
	// wenn id gleich -1 ist wird die gesamt Laustaerke verändert
	void set_volume(float volume, int id);
};

