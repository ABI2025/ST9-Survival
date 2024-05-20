#pragma once
#include "Utils/Log.h"
#include "Utils/Utils.h"




class Menu
{
public:
	Menu(const Menu&) = delete;
	//test
	static Menu* get_instance()
	{
		if (!s_instance)
			s_instance = new Menu;
		return s_instance;
	}
	static void delete_instance()
	{
		delete s_instance;
		s_instance = nullptr;
	}
	void show_menu();
	void button_events();

private:
	//Menu(): m_window(sf::VideoMode(1920, 1080), "Game") {}
	Menu();
	void draw_button_labels(int);
	sf::RenderWindow m_window;
	std::vector<std::string> m_name_button;
	//std::vector<std::vector<std::vector<Utils::Cell>>> m_map;
	inline static Menu* s_instance = nullptr;
	std::pair<sf::FloatRect, bool> m_buttons[3];
	sf::Font m_font;
};

