#include "Menu.h"
#include "Utils/Utils.h"
#include "Game.h"

constexpr int NUM_BUTTONS = 3;

void Menu::show_menu()
{
	Game::erstelleGame(m_window);
    //kommt noch
    while (m_window.isOpen())
    {
	    switch (0)
	    {
	    case 0: //start knopf
			Game::get_game()->runGame(0);
			break;
		case 1: //optionen oder so 
			LOG_ERROR("irgendwas ist schrecklich");
			break;
		case 2: //schlieﬂen
			LOG_ERROR("das darfst du nicht");
			m_window.close();
			break;
	    default:
			LOG_ERROR("bro how dafuq");
			break;
	    }
    }
}

void Menu::button_events()
{

}
