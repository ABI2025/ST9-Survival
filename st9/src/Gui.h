#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

//returns false on fail
bool init_sfml_imgui(sf::RenderWindow& window);




class GuiElement
{
	
};


class Gui
{
	std::vector<GuiElement> m_elements;
public:
	Gui(std::initializer_list<GuiElement>);
};

