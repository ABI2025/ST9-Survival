#include "BuildSystem.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "Tower.h"
#include "entities/EnemyManager.h"

BuildSystem::BuildSystem() : m_selected(Utils::Cell::NOTHING)
{
	m_texture_textures.resize(2);
	m_texture_sprites.resize(2);

	m_texture_textures[0].loadFromFile("resources/images/top.png");
	m_texture_textures[1].loadFromFile("resources/images/buttom.png");
	m_texture_sprites[0].setTexture(m_texture_textures[0]);
	m_texture_sprites[1].setTexture(m_texture_textures[1]);
	texture.create(135, 135);
	texture.clear(sf::Color::Transparent);
	texture.draw(m_texture_sprites[1]);
	texture.draw(m_texture_sprites[0]);
	texture.display();

	m_textures.resize(3);

	m_textures[0].loadFromFile("resources/images/charakter_HL.png");
	m_textures[1] = texture.getTexture();
	m_textures[2].loadFromFile("resources/images/1111.png");

	m_sprites.resize(4);

	m_sprites[0].setTexture(m_textures[0]);
	m_sprites[1].setTexture(m_textures[1]);
	m_sprites[2].setTexture(m_textures[1]);
	m_sprites[3].setTexture(m_textures[2]);
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
	ImGui::Begin("test");
	const float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
	const ImGuiStyle& style = ImGui::GetStyle();
	for (int i = 0; i < m_sprites.size(); i++)
	{
		std::string t = "test" + std::to_string(i);
		ImGui::PushID(i);
		if (ImGui::ImageButton(t.c_str(), m_sprites[i], { 135.0f,135.0f }))
		{
			//LOG_INFO("it works ig");
			m_selected = static_cast<Utils::Cell>(i);
		}

		const float last_button_x2 = ImGui::GetItemRectMax().x;
		const float next_button_x2 = last_button_x2 + style.ItemSpacing.x + 135.0f; // Expected position if next button was on same line
		if (i + 1 < m_sprites.size() && next_button_x2 < window_visible_x2)
			ImGui::SameLine();
		ImGui::PopID();
	}
	ImGui::End();
	return m_selected;
}

void BuildSystem::operator()(bool left_click, bool right_click, bool should_do_docking,
	std::vector<std::vector<std::vector<Utils::Cell>>>& map,
	std::vector<Tower>& towers,
	glm::ivec3 mouse_pos
	) const
{

	Utils::Pathfinding* pa = Utils::Pathfinding::get_instance();
	



	if (left_click && (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) || (should_do_docking && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow) && 
	ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow) )))
	{
		if (pa->is_valid(mouse_pos) && m_selected != Utils::Cell::NOTHING && map[0][mouse_pos.y][mouse_pos.x] != m_selected)
		{
			//set_map(selected, static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y), 0);
			if (m_selected == Utils::Cell::TURRET || m_selected == Utils::Cell::DEFENSE)
				towers.emplace_back(mouse_pos*135);
			if ((map[0][mouse_pos.y][mouse_pos.x] == Utils::Cell::DEFENSE || map[0][mouse_pos.y][mouse_pos.x] == Utils::Cell::TURRET)
				&& (m_selected != Utils::Cell::TURRET && m_selected != Utils::Cell::DEFENSE))
			{

				for (auto it = towers.begin(); it != towers.end();)
				{
					if ((it)->get_pos().x / 135.0f == mouse_pos.x && 
						(it)->get_pos().y / 135.0f == mouse_pos.y)
					{
						it = towers.erase(it);
					}
					else
					{
						++it;
					}
				}
			}
			map[0][mouse_pos.y][mouse_pos.x] = m_selected;
			EnemyManager::set_updated_tower(true);
		}
	}
	if (right_click && (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) || (should_do_docking && ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow) &&
		ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow))))
	{
		if (pa->is_valid(mouse_pos) && m_selected != Utils::Cell::NOTHING && map[0][mouse_pos.y][mouse_pos.x] != Utils::Cell::NOTHING)
		{
			//set_map(Utils::Cell::NOTHING, static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y), 0);
			if (map[0][mouse_pos.y][mouse_pos.x] == Utils::Cell::DEFENSE || map[0][mouse_pos.y][mouse_pos.x] == Utils::Cell::TURRET)
			{
				for (auto it = towers.begin(); it != towers.end();)
				{
					if ((it)->get_pos().x / 135.0f == mouse_pos.x &&
						(it)->get_pos().y / 135.0f == mouse_pos.y)
					{
						it = towers.erase(it);
					}
					else
					{
						++it;
					}
				}
			}
			map[0][mouse_pos.y][mouse_pos.x] = Utils::Cell::NOTHING;
			EnemyManager::set_updated_tower(true);
		}
	}
}
