#include "Optionen.h"

#include "imgui-sfml.h"
#include "imgui.h"
#include "sfml/Graphics.hpp"
#include "../Resources/Images/Roboto-Regular.embed"


Optionen::Optionen()
{
	m_sounds.add_group("player");
	m_sounds.add_group("music");
	m_sounds.load_buffer("resources/Sounds/Heilung.mp3", false, "player");
	m_sounds.load_buffer("resources/Sounds/Aufzeichnung(2).mp3", false, "player");
	m_sounds.load_buffer("resources/Sounds/hitmarker.ogg", false, "player");
	m_sounds.load_buffer("resources/Sounds/record.wav", true, "music");
	m_sounds.load_buffer("resources/Sounds/record-1.wav", true, "music");

}

bool Optionen::optionen_exe(sf::RenderWindow& window, bool in_game)
{
	std::vector<float> lautstarke = m_sounds.get_volumes();
	lautstarke[0] *= 100;
	lautstarke[1] *= 100;
	lautstarke[2] *= 100;
	bool open = true;
	sf::Clock deltaclock;
	while (window.isOpen() && open) {

		sf::Event event{};
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(window, event);
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					open = false;
				break;

			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}

		}
		ImGui::SFML::Update(window, deltaclock.restart());
		if (should_do_dockspace)
			ImGui::DockSpaceOverViewport();
		window.clear();
		ImGui::Begin("Fortnite(Optionen)");
		if (ImGui::Button("should do docking"))
		{
			should_do_dockspace = !should_do_dockspace;
		}



		ImGui::SliderFloat("Allgemein", &lautstarke[0], 0, 100);
		ImGui::SliderFloat("Player", &lautstarke[1], 0, 100);
		ImGui::SliderFloat("Musik", &lautstarke[2], 0, 100);
		m_sounds.set_volume(lautstarke[0], -1);
		m_sounds.set_volume(lautstarke[1], 0);
		m_sounds.set_volume(lautstarke[2], 1);

	
		if (ImGui::Button("close"))
		{
			ImGui::End();
			ImGui::SFML::Render(window);
			window.display();
			return false;
		}
		

		ImGui::End();
		ImGui::SFML::Render(window);
		window.display();
		
	}
	return true;
}
