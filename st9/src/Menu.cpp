#include "Menu.h"
#include "Utils/Utils.h"
#include "Game.h"
#include "Gui.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../Resources/Images/Roboto-Regular.embed"
#include "SFML/Audio.hpp"
#include "SFML/Opengl.hpp"

constexpr int NUM_BUTTONS = 3;
Menu::Menu() : m_window(sf::VideoMode(1920, 1080), "Game")
{
	m_name_button = { "Start","Options","Exit" };
	init_sfml_imgui(m_window);
	m_font.loadFromMemory(g_RobotoRegular, sizeof(g_RobotoRegular));
	// Initialisiere Buttons direkt im Konstruktor
	m_buttons[0].first = sf::FloatRect(1920.0f / 2.0f - 100.0f, 1080.0f / 2.0f - 200.0f, 200.0f, 50.0f); // Start-Button
	m_buttons[0].second = false;

	m_buttons[1].first = sf::FloatRect(1920.0f / 2.0f - 100.0f, 1080.0f / 2.0f - 100.0f, 200.0f, 50.0f); // Optionen
	m_buttons[1].second = false;

	m_buttons[2].first = sf::FloatRect(1920.0f / 2.0f - 100.0f, 1080.0f / 2.0f - 0.0f, 200.0f, 50.0f); // Schlieﬂen
	m_buttons[2].second = false;

	LOG_INFO("  OpenGL Info:");
	LOG_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
	LOG_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
	LOG_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
}

void Menu::show_menu()
{
	Game::erstelle_game(m_window);
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("resources/Sounds/Hitmarker.ogg")) { LOG_ERROR("fuck"); }
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setVolume(50.0f);
	sound.setRelativeToListener(true);
	m_window.setFramerateLimit(60);
	sf::Clock deltaClock;
	while (m_window.isOpen())
	{

		sf::Event event{};
		while (m_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(m_window, event);
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					m_window.close();
				break;

			case sf::Event::Closed:
				m_window.close();
				break;
			default:
				break;
			}

		}
		ImGui::SFML::Update(m_window, deltaClock.restart());
		ImGui::ShowDemoWindow();

		sf::FloatRect mouse = { sf::Vector2f(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))), {1, 1} };

		int button_index = -1;
		for (int i = 0; i < NUM_BUTTONS; ++i)
		{
			if (m_buttons[i].first.intersects(mouse))
			{
				button_index = i;
				if (!m_buttons[i].second)
				{
					sound.play();
				}
				m_buttons[i].second = true;
				//break; //entfernt weil es theoretisch mˆglich ist, dass jemand von einem zum anderen frame von einem knopf zum andern geht.
			}
			else
				m_buttons[i].second = false;
		}

		if (button_index != -1 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			switch (button_index)
			{
			case 0: // Start-Button

				m_window.clear();//damit falls hier eine imgui sachen passiert w‰re nichts crasht
				ImGui::SFML::Render(m_window);
				m_window.display();

				Game::get_game()->run_game(0);
				break;
			case 1: // Optionen

				break;
			case 2: // Schlieﬂen
				m_window.close();
				break;
			default:
				LOG_ERROR("what in the memory corruption");
				break;
			}
		}

		m_window.clear();

		// Zeichne sichtbare Buttons und Labels
		for (const auto& [rect, pressed] : m_buttons)
		{
			sf::RectangleShape button_shape(sf::Vector2f(rect.width, rect.height));
			button_shape.setPosition(rect.left, rect.top);
			button_shape.setFillColor(pressed ? sf::Color(183, 65, 14) : sf::Color::Red); // Farbe der Buttons
			m_window.draw(button_shape);
		}
		draw_button_labels(NUM_BUTTONS);
		ImGui::SFML::Render(m_window);
		m_window.display();
	}
}

void Menu::draw_button_labels(const int numButtons)
{
	for (int i = 0; i < numButtons; i++)
	{
		sf::Text button_text;
		button_text.setFont(m_font); // Stelle sicher, dass die Schriftart geladen ist
		button_text.setString(m_name_button[i]); // Setze den Button-Text
		button_text.setCharacterSize(24); // W‰hle eine Textgrˆﬂe
		button_text.setPosition(m_buttons[i].first.left + 20, m_buttons[i].first.top + 10); // Positioniere den Text innerhalb des Buttons
		button_text.setFillColor(sf::Color::White); // Textfarbe

		m_window.draw(button_text);
	}
}

void Menu::button_events()
{

}
