﻿// ReSharper disable CppTooWideScopeInitStatement
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

BuildSystem::BuildSystem() : m_selected(Utils::Cell::NOTHING)
{
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

	m_textures[0].loadFromFile("resources/images/charakter_HL.png");
	m_textures[1] = m_texture.getTexture();
	m_textures[2].loadFromFile("resources/images/1111.png");

	m_sprites.resize(8);

	m_sprites[0].setTexture(m_textures[0]);

	m_sprites[1].setTexture(m_textures[1]);
	m_sprites[2].setTexture(m_textures[1]);
	m_sprites[3].setTexture(m_textures[1]);
	m_sprites[4].setTexture(m_textures[1]);
	m_sprites[5].setTexture(m_textures[1]);
	m_sprites[6].setTexture(m_textures[1]);

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

	m_id = -1;
	for (uint32_t current_button_id = 0; current_button_id < m_sprites.size(); current_button_id++)
	{
		std::string button_id = "test" + std::to_string(current_button_id);
		ImGui::PushID(current_button_id);
		if (ImGui::ImageButton(button_id.c_str(), m_sprites[current_button_id], { 135.0f,135.0f }))
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
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) // With a delay
			ImGui::SetTooltip("I am a tooltip with a delay.");
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

	if (!pa->is_valid(mouse_pos/135.0f))
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
	glm::ivec3 cell_mouse_pos = mouse_pos/135.0f;
	if (left_click && is_windows_focused)
	{
		if (m_selected != Utils::Cell::NOTHING && map[0][cell_mouse_pos.y][cell_mouse_pos.x] != m_selected)
		{
			//set_map(selected, static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y), 0);

			if ((m_selected != map[0][cell_mouse_pos.y][cell_mouse_pos.x]))
			{
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x].reset();
				if (m_selected != Utils::Cell::TURRET)
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

			if ((m_selected == Utils::Cell::TURRET)
				&&
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] != Utils::Cell::TURRET)
			{
				towers.emplace_back(std::make_shared<Tower>(cell_mouse_pos * 135));
				entities.push_back(towers.back());
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x] = towers.back();
			}
			else if (m_selected == Utils::Cell::WALL &&
				map[0][cell_mouse_pos.y][cell_mouse_pos.x] != Utils::Cell::WALL)
			{
				entities.emplace_back(std::make_shared<Wall>(cell_mouse_pos * 135));
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x] = entities.back();
			}
			map[0][cell_mouse_pos.y][cell_mouse_pos.x] = m_selected;
			EnemyManager::set_updated_tower(true);
		}
	}
	if (right_click && is_windows_focused)
	{
		if (m_selected != Utils::Cell::NOTHING && map[0][cell_mouse_pos.y][cell_mouse_pos.x] != Utils::Cell::NOTHING)
		{
			//set_map(Utils::Cell::NOTHING, static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y), 0);
			if (map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::TURRET || map[0][cell_mouse_pos.y][cell_mouse_pos.x] == Utils::Cell::WALL)
			{
				Game::get_game()->getEntityMap()[0][cell_mouse_pos.y][cell_mouse_pos.x].reset();

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
			map[0][cell_mouse_pos.y][cell_mouse_pos.x] = Utils::Cell::NOTHING;
			EnemyManager::set_updated_tower(true);
		}
	}
}
