#pragma once
#include <deque>
#include <vector>
#include <SFML/Audio.hpp>

class Sounds
{
	std::vector<sf::SoundBuffer> m_buffers;
	std::vector<std::pair<std::deque<sf::Sound>,bool>> m_sounds;
public:
	Sounds() = default;
	~Sounds();
	//fügt einen sound hinzu und spielt ihn ab
	void add_sound(int id);

	//Löscht alle nicht spielenden Sounds
	void cleanup(bool priority_ignorieren);

	//Lädt eine music file spezifiziert in location und erstellt eine neue deque für sounds
	void load_buffer(const std::string& location, bool priority);

	//pausiert alle nicht gestoppten lieder
	void pause_all(bool priority_ignorieren);

	//spielt alle sounds ab die nicht gerade abgespielt werden
	void play_all();

	//löscht alle buffer und sounds
	void clear_all();
};

