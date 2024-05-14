#pragma once
#include <deque>
#include <map>
#include <vector>
#include <SFML/Audio.hpp>

class Sounds
{
	std::map<std::string,std::vector<sf::SoundBuffer>> m_buffers;
	std::map<std::string,std::vector<std::pair<std::deque<sf::Sound>,bool>>> m_sounds;


	std::map<std::string,float> m_volumes;
	std::map<int,std::string> m_mapping;
public:
	Sounds();
	~Sounds();
	//f�gt einen sound hinzu und spielt ihn ab
	void add_sound(int group_id,int id);

	//f�gt einen sound hinzu und spielt ihn ab
	void add_sound(const std::string& group_id,int id);

	//L�scht alle nicht spielenden Sounds
	void cleanup(bool priority_ignorieren);

	//L�dt eine music file spezifiziert in location und erstellt eine neue deque f�r sounds
	void load_buffer(const std::string& location, bool priority, const std::string& group);

	//
	void add_group(const std::string& group);

	//pausiert alle nicht gestoppten lieder
	void pause_all(bool priority_ignorieren);
		
	//spielt alle sounds ab die nicht gerade abgespielt werden
	void play_all();

	//l�scht alle buffer und sounds
	void clear_all();

	// setzt die lautst�rke von allen sounds der entsprechenden id auf volume
	// wenn id gleich -1 ist wird die gesamt laust�rke ver�ndert
	void set_volume(float volume,int id);
};

