// ReSharper disable CppTooWideScopeInitStatement
#include "BuildSystem.h"
#include "Game.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Tower.h"
#include "entities/EnemyManager.h"

#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>

#include "Wall.h"

constexpr float CellSize = 135.0f;


BuildSystem::BuildSystem() : m_selected(Utils::Cell::NOTHING)
{
	m_costs.insert({0,100});
	m_costs.insert({1,200});
	m_costs.insert({2,300});
	m_costs.insert({3,400});
	m_costs.insert({4,500});
	m_costs.insert({5,600});
	//prophesionallen coding

	m_texture_textures.resize(2);
	m_texture_sprites.resize(2);

	m_texture_textures[0].loadFromFile("resources/images/top.png");
	m_texture_textures[1].loadFromFile("resources/images/buttom.png");
	m_texture_sprites[0].setTexture(m_texture_textures[0]);
	m_texture_sprites[1].setTexture(m_texture_textures[1]);
	m_texture.create(135, 135);
	m_texture.clear(sf::Color::Transparent);
	m_texture.draw(m_texture_sprites[1]);
	m_texture.draw(m_texture_sprites[0]);
	m_texture.display();

	m_textures.resize(3);

	m_textures[0].loadFromFile("resources/images/none.png");
	m_textures[1] = m_texture.getTexture();
	m_textures[2].loadFromFile("resources/images/1111.png");

	m_sprites.resize(8);

	m_sprites[0].setTexture(m_textures[0]);
	m_sprites[0].setColor(sf::Color::Transparent);
	
	m_sprites[1].setTexture(m_textures[1]);
	m_sprites[2].setTexture(m_textures[1]);
	m_sprites[3].setTexture(m_textures[1]);
	m_sprites[4].setTexture(m_textures[1]);
	m_sprites[5].setTexture(m_textures[1]);
	m_sprites[6].setTexture(m_textures[1]);

	m_sprites[1].setColor(sf::Color::Magenta);
	m_sprites[2].setColor(sf::Color::Yellow);
	m_sprites[3].setColor(sf::Color::White);
	m_sprites[4].setColor(sf::Color::Red);
	m_sprites[5].setColor(sf::Color::Blue);
	m_sprites[6].setColor(sf::Color::Black);

	m_sprites[7].setTexture(m_textures[2]);
}

Utils::Cell BuildSystem::display()
{
	//texture.clear(sf::Color::Transparent);
	//texture.draw(m_texture_sprites[1]);
	//texture.draw(m_texture_sprites[0]);
	//texture.display();
	//m_textures[1] = texture.getTexture();
	//m_sprites[1].setTexture(m_textures[1]);
	//m_sprites[2].setTexture(m_textures[1]);
	ImGui::Begin("Build System");
	const float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
	const ImGuiStyle& style = ImGui::GetStyle();
	if(m_selected != Utils::Cell::TURRET)
		m_id = -1;
	for (uint32_t current_button_id = 0; current_button_id < m_sprites.size(); current_button_id++)
	{
		std::string button_id = "test" + std::to_string(current_button_id);
		ImGui::PushID(current_button_id);
		if (ImGui::ImageButton(button_id.c_str(), m_sprites[current_button_id], { 135.0f,135.0f },m_sprites[current_button_id].getColor()))
		{

			//LOG_INFO("it works ig");
			int temp;
			if (current_button_id == 0)
			{
				temp = 0;
			}
			else if (current_button_id > 0 && current_button_id < 7)
			{
				m_id = current_button_id - 1;
				temp = 1;
			}
			else
			{
				temp = current_button_id - 5;
			}
			m_selected = static_cast<Utils::Cell>(temp);
		}
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
		{
			switch (current_button_id)
			{
			case 0:
				ImGui::BeginTooltip();
				ImGui::Text("Nichts");
				ImGui::EndTooltip();
				break;
			case 1:
				ImGui::BeginTooltip();
				ImGui::Text("Basic:");
				ImGui::Text("200 leben");
				ImGui::Text("%.0f geld",m_costs[0]);
				ImGui::EndTooltip();
				break;
			case 2:
				ImGui::BeginTooltip();
				ImGui::Text("Ein Turm mit:");
				ImGui::Text("300 leben");
				ImGui::Text("%.0f geld", m_costs[1]);
				ImGui::EndTooltip();
				break;
			case 3:
				ImGui::BeginTooltip();
				ImGui::Text("Ein Turm mit:");
				ImGui::Text("400 leben");
				ImGui::Text("%.0f geld", m_costs[2]);
				ImGui::EndTooltip();
				break;
			case 4:
				ImGui::BeginTooltip();
				ImGui::Text("Ein Turm mit:");
				ImGui::Text("500 leben");
				ImGui::Text("%.0f geld", m_costs[3]);
				ImGui::EndTooltip();
				break;
			case 5:
				ImGui::BeginTooltip();
				ImGui::Text("Ein Turm mit:");
				ImGui::Text("600 leben");
				ImGui::Text("%.0f geld", m_costs[4]);
				ImGui::EndTooltip();
				break;

			case 6:
				ImGui::BeginTooltip();
				ImGui::Text("Bigus Chungus");
				ImGui::Text("700 leben");
				ImGui::Text("%.0f geld", m_costs[5]);
				ImGui::EndTooltip();
				break;
			case 7:
				ImGui::BeginTooltip();
				ImGui::Text("Eine Wand mit:");
				ImGui::Text("500 leben");
				ImGui::Text("25.0  Geld");
				ImGui::EndTooltip();
				break;
			default:
				ImGui::SetTooltip("I am a tooltip with a delay.");
				break;
			}
		}
		const float last_button_x2 = ImGui::GetItemRectMax().x;
		const float next_button_x2 = last_button_x2 + style.ItemSpacing.x + 135.0f; // Expected position if next button was on same line
		if (current_button_id + 1 < m_sprites.size() && next_button_x2 < window_visible_x2)
			ImGui::SameLine();
		ImGui::PopID();
	}
	ImGui::End();
	return m_selected;
}

void BuildSystem::operator()(bool left_click, bool right_click, bool should_do_docking,
	std::vector<std::vector<std::vector<Utils::Cell>>>& map,
	std::vector<std::shared_ptr<Entity>>& entities,
	std::vector<std::shared_ptr<Tower>>& towers,
	glm::vec3 mouse_pos
	) const
{


	Utils::Pathfinding* pa = Utils::Pathfinding::get_instance();
	// Überprüfen, ob die Mausposition eine gültige Zelle ist
	if (!pa->is_valid(mouse_pos / CellSize))
		return;

	const bool is_windows_focused =
		( //wenn das haupt fenster kein dockspace ist wird geguckt ob irgendeins der ImGui Fenster gefocused ist oder ob eins gehovered ist
			!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) &&
			!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)
			)
		||
		( //wenn das Haupt Fenster ein Dockspace ist, sind wir gerade in dem ImGui Fenster deshalb gucken wir ob das momentane Gefocused ist und gehovered
			should_do_docking &&
			ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow) &&
			ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow)
			);


	// Berechnung der Zellposition der Maus
	const glm::ivec3 cell_mouse_pos = mouse_pos / CellSize;

	// Behandlung von Linksklicks
	if (left_click && is_windows_focused)
	{
		// Überprüfen, ob eine Zelle ausgewählt ist und ob die aktuelle Zelle leer ist
		if (m_selected != Utils::Cell::NOTHING
			&&
			map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::NOTHING
			&&
			map[0][cell_mouse_pos.y][cell_mouse_pos.x] != m_selected)
		{
			// Platzierung eines Turms
			LOG_INFO("m_ID: {}", m_id);
			if (m_selected == Utils::Cell::TURRET &&
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] != Utils::Cell::TURRET &&
				(Game::get_game()->m_geld >= m_costs.at(m_id)))
			{
				(*Game::get_game()).add_geld(-m_costs.at(m_id));
				std::shared_ptr<Tower> tower = std::make_shared<Tower>(cell_mouse_pos * 135,static_cast<towerKind>(m_id),static_cast<int>(m_costs.at(m_id)));
				towers.emplace_back(tower);
				entities.push_back(tower);
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x] = tower;
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] = m_selected;
				EnemyManager::set_updated_tower(true);
			}
			//platzierung einer Mauer
			else if (m_selected == Utils::Cell::WALL &&
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] != Utils::Cell::WALL &&
				(Game::get_game()->m_geld >= 25))
			{
				Game::get_game()->add_geld(-25);
				entities.emplace_back(std::make_shared<Wall>(cell_mouse_pos * 135));
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x] = entities.back();
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] = m_selected;
				EnemyManager::set_updated_tower(true);
			}
			// Aktualisieren der Karte
			
		}
	}

	// Behandlung von Rechtsklicks
	if (right_click && is_windows_focused)
	{
		// Überprüfen, ob eine Zelle ausgewählt ist und ob die aktuelle Zelle nicht leer ist
		if (m_selected != Utils::Cell::NOTHING &&
			map[0][cell_mouse_pos.y][cell_mouse_pos.x] != Utils::Cell::NOTHING)
		{

			// Entfernen eines Turms oder einer Mauer
			if (map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::TURRET ||
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::WALL)
			{
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x].reset();

				// Entfernen eines Turms
				if (map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::TURRET)
				{
					for (auto it = towers.begin(); it != towers.end();)
					{
						if ((*it)->get_pos().x / 135.0f == cell_mouse_pos.x &&
							(*it)->get_pos().y / 135.0f == cell_mouse_pos.y)
						{

							it->reset();
							it = towers.erase(it);
						}
						else
						{
							++it;
						}
					}
				}

				// Entfernen der Entität
				for (auto it = entities.begin(); it != entities.end();)
				{
					if ((*it)->get_pos().x / 135.0f == cell_mouse_pos.x &&
						(*it)->get_pos().y / 135.0f == cell_mouse_pos.y)
					{
						it->reset();
						it = entities.erase(it);
					}
					else
					{
						++it;
					}
				}
			}
			// Aktualisieren der Karte
			map[0][cell_mouse_pos.y][cell_mouse_pos.x] = Utils::Cell::NOTHING;
			EnemyManager::set_updated_tower(true);
		}
	}
}
