#include "Menu.h"
#include "Utils/Utils.h"
#include "Game.h"
#include "Gui.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../Resources/Images/Roboto-Regular.embed"
#include "SFML/Audio.hpp"
#include "SFML/OpenGL.hpp"
#include "Optionen.h"
#include "Tower.h"
#include "Wall.h"
#include "entities/EnemyManager.h"

constexpr int NUM_BUTTONS = 4;
Menu::Menu() : m_window(sf::VideoMode(1920, 1080), "Game")
{
	m_name_button = { "Start","Options","Exit","Story"};
	init_sfml_imgui(m_window);
	m_font.loadFromMemory(g_RobotoRegular, sizeof(g_RobotoRegular));
	// Initialisiere Buttons direkt im Konstruktor
	m_buttons[0].first = sf::FloatRect(1920.0f / 2.0f - 100.0f, 1080.0f / 2.0f - 200.0f, 200.0f, 50.0f); // Start-Button
	m_buttons[0].second = false;

	m_buttons[1].first = sf::FloatRect(1920.0f / 2.0f - 100.0f, 1080.0f / 2.0f - 100.0f, 200.0f, 50.0f); // Optionen
	m_buttons[1].second = false;

	m_buttons[2].first = sf::FloatRect(1920.0f / 2.0f - 100.0f, 1080.0f / 2.0f - 0.0f, 200.0f, 50.0f); // Schlieﬂen
	m_buttons[2].second = false;
	
	m_buttons[3].first = sf::FloatRect(1920.0f / 2.0f - 100.0f, 1080.0f / 2.0f + 100.0f, 200.0f, 50.0f); // Story
	m_buttons[3].second = false;

	LOG_INFO("  OpenGL Info:");
	LOG_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
	LOG_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
	LOG_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
}

Menu* Menu::get_instance()
{
	if (!s_instance)
		s_instance = new Menu;
	return s_instance;
}

void Menu::delete_instance()
{
	delete s_instance;
	s_instance = nullptr;
}

void Menu::show_menu()
{
	Optionen* opt = Optionen::get_instance();
	Game::erstelle_game(m_window,opt->get_sounds());
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Resources/Sounds/Hitmarker.ogg")) { LOG_ERROR("sound konnte nicht geladen werden"); }

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

		sf::FloatRect mouse = { sf::Vector2f(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))), {1, 1} };

		int button_index = -1;
		for (int i = 0; i < NUM_BUTTONS; ++i)
		{
			if (m_buttons[i].first.intersects(mouse))
			{
				button_index = i;
				if (!m_buttons[i].second)
				{
					opt->get_sounds().add_sound("player", 2);
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
			case 1: 
				m_window.clear();//damit falls hier eine imgui sachen passiert w‰re nichts crasht
				ImGui::SFML::Render(m_window);
				m_window.display();

				opt->optionen_exe(m_window,false);

				break;
			case 2: // Schlieﬂen
				m_window.close();
				break;
			case 3: // Story
				m_window.clear();//damit falls hier eine imgui sachen passiert w‰re nichts crasht
				ImGui::SFML::Render(m_window);
				story();
				m_window.display();
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
	Optionen::delete_instance();
	WallTexture::delete_instance();
	TowerTexture::delete_instance();
	ProjectileTexture::delete_instance();
	opt = nullptr;
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

void Menu::story()
{
	bool show_story_window = true;

	while (m_window.isOpen() && show_story_window)
	{
		sf::Event event{};
		while (m_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(m_window, event);
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				return;
			}
			
		}

		ImGui::SFML::Update(m_window, sf::seconds(1.f / 60.f));

		m_window.clear();

		// Set the window size to be wide
		ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		ImGui::Begin("Story", &show_story_window, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::BeginChild("StoryText", ImVec2(780, 540), true, ImGuiWindowFlags_HorizontalScrollbar);

		ImGui::TextWrapped("Inmitten einer verlassenen Stadt erhebt sich ein uralter Turm, ein Relikt aus einer laengst vergangenen Zeit. Dieser Turm, der inmitten moderner Ruinen steht, birgt ein Geheimnis, das ueber die Jahrhunderte hinweg vergessen wurde. Doch jetzt ist er das Ziel von Geistern und uebernatuerlichen Kreaturen, die aus dem Schatten auftauchen und versuchen, den Turm zu erobern.\n\n"
			"Du bist ein erfahrener Soldat, geschickt im Umgang mit modernen Waffen und Technologien. Deine Mission: Den Turm um jeden Preis verteidigen. Ausgestattet mit einem Arsenal an Maschinengewehren, Granatwerfern und High-Tech-Verteidigungssystemen, musst du dich den Horden von Geistern stellen, die in Wellen angreifen.\n\n"
			"Die Regierung hat dich beauftragt, diesen strategisch wichtigen Punkt zu halten. Der Turm ist nicht nur ein Symbol der Vergangenheit, sondern auch ein Knotenpunkt fuer Kommunikations- und Ueberwachungssysteme, die fuer die Sicherheit der gesamten Region von entscheidender Bedeutung sind.\n\n"
			"Waehrend du dich vorbereitest, denkst du an die letzten Worte deines Kommandanten: \"Dies ist nicht nur ein Kampf gegen die Geister, sondern ein Kampf fuer die Zukunft unserer Welt. Halte den Turm um jeden Preis.\"\n\n"
			"Deine Ressourcen sind begrenzt, aber du erhaeltst fuer jede ueberstandene Angriffswelle Belohnungen in Form von Geld und Materialien. Diese kannst du nutzen, um deine Verteidigungen zu verbessern, neue Waffen zu kaufen und schuetzende Mauern zu errichten, die dir im Kampf gegen die immer staerkeren Geisterhorden helfen werden.\n\n"
			"Mit jedem Angriff lernst du mehr ueber deine Feinde und findest Wege, ihre Schwaechen auszunutzen. Du musst taktisch vorgehen, deine Ressourcen klug einsetzen und deine Verteidigungen stetig verbessern, um den Turm zu schuetzen.\n\n"
			"Bereite dich vor, Soldat. Die Geister werden kommen, und sie sind zahlreich und gnadenlos. Aber mit deinem Mut, deinem Geschick und deinen modernen Waffen hast du die Macht, sie aufzuhalten. Der Turm muss gehalten werden, und das Schicksal der Stadt liegt in deinen Haenden.\n\n"
			"Lass den Kampf beginnen!");

		ImGui::EndChild();

		if (ImGui::Button("Close"))
		{
			show_story_window = false;
		}

		ImGui::End();

		ImGui::SFML::Render(m_window);
		m_window.display();
	}
}




