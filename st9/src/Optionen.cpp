#include "Optionen.h"

#include "imgui-sfml.h"
#include "imgui.h"
#include "sfml/Graphics.hpp"
#include "../Resources/Images/Roboto-Regular.embed"


Optionen::Optionen()
{

}

void Optionen::optionen_exe(sf::RenderWindow& window)
{
	float lautstarke[3] = { 10.0f,10.0f,10.0f };
	
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


		ImGui::SliderFloat("Allgemein", lautstarke, 0, 100);
		ImGui::SliderFloat("Player", &lautstarke[1], 0, 100);
		ImGui::SliderFloat("Musik", &lautstarke[2], 0, 100);
		m_sounds.set_volume(lautstarke[0], -1);
		m_sounds.set_volume(lautstarke[1], 0);
		m_sounds.set_volume(lautstarke[2], 1);

		ImGui::End();
		ImGui::SFML::Render(window);
		window.display();
		
	}
}
