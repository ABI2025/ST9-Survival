#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "Sounds.h"

class Optionen
{
	inline static Optionen* s_instance;
public:
	void optionen_exe(sf::RenderWindow&);
	static Optionen* get_instance()
	{
		if (!s_instance)
			s_instance = new Optionen;
		return s_instance;
	}
private:
	bool should_do_dockspace;
	Optionen();
	Sounds m_sounds;
	std::vector<std::string> m_name_button;
	std::pair<sf::FloatRect, bool> m_buttons[11];
	sf::Font m_font;

};

