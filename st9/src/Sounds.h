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
	//f�gt einen sound hinzu und spielt ihn ab
	void add_sound(int id);

	//L�scht alle nicht spielenden Sounds
	void cleanup(bool priority_ignorieren);

	//L�dt eine music file spezifiziert in location und erstellt eine neue deque f�r sounds
	void load_buffer(const std::string& location, bool priority);

	//pausiert alle nicht gestoppten lieder
	void pause_all(bool priority_ignorieren);

	//spielt alle sounds ab die nicht gerade abgespielt werden
	void play_all();

	//l�scht alle buffer und sounds
	void clear_all();
};

