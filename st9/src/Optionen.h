#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "Sounds.h"

class Optionen
{
	inline static Optionen* s_instance;
public:
	bool optionen_exe(sf::RenderWindow& , bool in_game);
	static Optionen* get_instance();

	static void delete_instance();


	bool get_should_do_dockspace() const;

	Sounds& get_sounds();

private:
	bool should_do_dockspace;
	Optionen();
	Sounds m_sounds;
	//std::vector<std::string> m_name_button;
	//std::pair<sf::FloatRect, bool> m_buttons[11];
	//sf::Font m_font;

};

