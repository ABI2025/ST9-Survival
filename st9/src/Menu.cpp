#include "Menu.h"
#include "Utils/Utils.h"
#include "Game.h"
#include "Gui.h"
#include "../Resources/Roboto-Regular.embed"
#include "SFML/Audio.hpp"

constexpr int NUM_BUTTONS = 3;
Menu::Menu() : m_window(sf::VideoMode(1920, 1080), "Game") {
	m_name_button = { "Start","Options","Exit" };
	init_sfml_imgui(m_window);
	font.loadFromMemory(g_RobotoRegular, sizeof(g_RobotoRegular));
	// Initialisiere Buttons direkt im Konstruktor
	buttons[0].first = sf::FloatRect(1920 / 2 - 100, 1080 / 2 - 200, 200, 50); // Start-Button
	buttons[0].second = false;

	buttons[1].first = sf::FloatRect(1920 / 2 - 100, 1080 / 2 - 100, 200, 50); // Optionen
	buttons[1].second = false;

	buttons[2].first = sf::FloatRect(1920 / 2 - 100, 1080 / 2 - 0, 200, 50); // Schlieﬂen
	buttons[2].second = false;

}

void Menu::show_menu() {
	Game::erstelle_game(m_window);
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Resources/Hitmarker.wav")) LOG_ERROR("fuck");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setVolume(50.0f);
	m_window.setFramerateLimit(60);
	
	while (m_window.isOpen())
	{

		sf::Event event;
		while (m_window.pollEvent(event)) 
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					m_window.close();
				break;

			case sf::Event::Closed:
					m_window.close();
				break;
			}

		}

		sf::FloatRect mouse = { sf::Vector2f(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))), {1, 1} };

		int buttonIndex = -1;
		for (int i = 0; i < NUM_BUTTONS; ++i) 
		{
			if (buttons[i].first.contains(mouse.left, mouse.top)) 
			{
				buttonIndex = i;
				if (!buttons[i].second)
				{
					sound.play();
				}
				buttons[i].second = true;
				//break; //entfernt weil es theoretisch mˆglich ist, dass jemand von einem zum anderen frame von einem knopf zum andern geht.
			}
			else
				buttons[i].second = false;
		}

		if (buttonIndex != -1 && sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		{
			switch (buttonIndex)
			{
			case 0: // Start-Button
				Game::get_game()->run_game(0);
				break;
			case 1: // Optionen
				//LOG_ERROR("irgendwas ist schrecklich");
				break;
			case 2: // Schlieﬂen
				//LOG_DEBUG("das darfst du nicht");
				m_window.close();
				break;
			default:
				LOG_WARN("how the ...");
				break;
			}
		}

		m_window.clear();

		// Zeichne sichtbare Buttons und Labels
		for (const auto& button : buttons) 
		{
			sf::RectangleShape buttonShape(sf::Vector2f(button.first.width, button.first.height));
			buttonShape.setPosition(button.first.left, button.first.top);
			buttonShape.setFillColor(button.second ? sf::Color(183, 65, 14) : sf::Color::Red); // Farbe der Buttons
			m_window.draw(buttonShape);
		}
		draw_button_labels(NUM_BUTTONS);

		m_window.display();
	}
}

void Menu::draw_button_labels(int numButtons)
{
	for (int i = 0; i < numButtons; i++) 
	{
		sf::Text buttonText;
		buttonText.setFont(font); // Stelle sicher, dass die Schriftart geladen ist
		buttonText.setString(m_name_button[i]); // Setze den Button-Text
		buttonText.setCharacterSize(24); // W‰hle eine Textgrˆﬂe
		buttonText.setPosition(buttons[i].first.left + 20, buttons[i].first.top + 10); // Positioniere den Text innerhalb des Buttons
		buttonText.setFillColor(sf::Color::White); // Textfarbe

		m_window.draw(buttonText);
	}
}

void Menu::button_events()
{

}
