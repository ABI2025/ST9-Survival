#include "Menu.h"
#include "Utils/Utils.h"
#include "Game.h"

constexpr int NUM_BUTTONS = 3;

void Menu::show_menu()
{
	Game::erstelleGame(m_window);
    //kommt noch
    //while (m_window.isOpen())
    //{
    //    sf::Event event{};
    //    while (m_window.pollEvent(event))
    //    {
    //        switch (event.type)
    //        {
    //        case sf::Event::KeyPressed:
    //            if (event.key.code == sf::Keyboard::Key::Escape)
    //            {
    //                m_window.close();
    //            }
    //        	break;
    //            //fallthrough
    //        case sf::Event::Closed:
    //            m_window.close();
    //            break;
    //        }
    //    }
    //    m_window.clear();
    //    m_window.display();
    //}


    Game::get_game()->runGame(0);

}

void Menu::button_events()
{

}
