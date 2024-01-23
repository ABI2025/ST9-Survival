#pragma once
#include "Utils/Log.h"
#include "Utils/Utils.h"




class Menu
{
public:
	Menu(const Menu&) = delete;
	//test
	static Menu* get()
	{
		if (!s_Instance)
			s_Instance = new Menu;
		return s_Instance;
	}
	void show_menu();
	void button_events();

private:
	//Menu(): m_window(sf::VideoMode(1920, 1080), "Game") {}
	Menu();
	void drawButtonLabels(int);
	sf::RenderWindow m_window;
	std::vector<std::string> nameButton;
	std::vector<std::vector<std::vector<Utils::Cell>>> m_map;
	inline static Menu* s_Instance = nullptr;
	std::pair<sf::FloatRect,bool> buttons[3];
	sf::Font font;
};

