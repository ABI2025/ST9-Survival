#include "Optionen.h"

#include "imgui-SFML.h"
#include "imgui.h"
#include "SFML/Graphics.hpp"
#include "../Resources/Images/Roboto-Regular.embed"


Optionen::Optionen()
{
	m_sounds.add_group("player");
	m_sounds.add_group("music");
	m_sounds.load_buffer("Resources/Sounds/Heilung.mp3", false, "player");
	m_sounds.load_buffer("Resources/Sounds/Aufzeichnung(2).mp3", false, "player");
	m_sounds.load_buffer("Resources/Sounds/hitmarker.ogg", false, "player");
	m_sounds.load_buffer("Resources/Sounds/record.wav", true, "music");
	m_sounds.load_buffer("Resources/Sounds/record-1.wav", true, "music");
	std::ifstream fin("optionen.txt");
	if (fin.is_open())
	{
		std::string line;
		std::getline(fin, line, ';');
		should_do_dockspace = std::stoi(line);
		std::getline(fin, line, ';');
		float volume1 = std::stof(line);
		std::getline(fin, line, ';');
		float volume2 = std::stof(line);
		std::getline(fin, line, ';');
		float volume3 = std::stof(line);

		m_sounds.set_volume(volume1 * 100, -1);
		m_sounds.set_volume(volume2 * 100, 0);
		m_sounds.set_volume(volume3 * 100, 1);
	}
	else
	{
		std::ofstream fout("optionen.txt");
		fout.close();
	}

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

		ImGui::Text("W, A, S, D: Bewegen des Spielers (W = Hoch, A = Links, S = Runter, D = Rechts)");
		ImGui::Text("Linke Maustaste: Platzieren eines Turms oder einer Mauer an der aktuellen Mausposition");
		ImGui::Text("Rechte Maustaste: Entfernen eines Turms oder einer Mauer an der aktuellen Mausposition");
		ImGui::Text("ESC: Pausiert das Spiel und oeffnet das Optionsmenue");
		ImGui::Text("F: Abfeuern eines Projektils in Richtung der Maus");
	
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

Optionen* Optionen::get_instance()
{
	if (!s_instance)
		s_instance = new Optionen;
	return s_instance;
}

void Optionen::delete_instance()
{
	if (!s_instance)
		return;
	s_instance->m_sounds.clear_all();

	const std::vector<float> volumes = s_instance->m_sounds.get_volumes();
	std::ofstream fout("optionen.txt");
	fout << s_instance->should_do_dockspace << ';' << volumes[0] << ';' << volumes[1] << ';' << volumes[2];
	fout.close();
	delete s_instance;
	s_instance = nullptr;
}

bool Optionen::get_should_do_dockspace() const
{
	return should_do_dockspace;
}

Sounds& Optionen::get_sounds()
{
	return m_sounds;
}
