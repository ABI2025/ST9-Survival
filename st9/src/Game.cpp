#include "Game.h"
#include "healthbar.h"
#include <complex>
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <imgui.h>
#include <SFML/Audio.hpp>

#include "Camera.h"
#include "imgui-SFML.h"
#include "entities/Player/Player.h"
#include "entities/EnemyManager.h"
#include "MainBuilding.h"
#include "BuildSystem.h"
#include "imgui_internal.h"
#include "Projektil.h" //können wir später löschen, ist nur zum debuggen hier
#include "Sounds.h"
#include "Tower.h"

constexpr int BACKGROUND_HEIGHT = 135;
constexpr int BACKGROUND_WIDTH = 135;

constexpr int height = 21;
constexpr int width = 41;

std::vector<std::vector<std::array<uint8_t, 2>>> erstelle_map()
{
	std::vector<std::vector<std::array<uint8_t, 2>>> karte;
	std::array<uint8_t, 2> single_cell = { 0,0 };
	for (int i = 0; i < width; i++)
	{
		std::vector<std::array<uint8_t, 2>> inner_map;
		for (int j = 0; j < height; j++)
		{
			single_cell[0] = Utils::Random::UInt(0, 3);
			inner_map.emplace_back(single_cell);

		}
		karte.emplace_back(inner_map);
	}
	return karte;
}

Game::Game(sf::RenderWindow& window) :m_window(window)
{
	//window.setFramerateLimit(2);
	m_background_textures.resize(4);

	if (!m_background_textures[0].loadFromFile("Resources/images/Background1.jpg")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	if (!m_background_textures[1].loadFromFile("Resources/images/Background2.jpg")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	if (!m_background_textures[2].loadFromFile("Resources/images/Background3.jpg")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	if (!m_background_textures[3].loadFromFile("Resources/images/Background4.jpg")) { LOG_ERROR("texture konnte nicht geladen werden"); }

	m_background_sprites.resize(4);

	m_background_sprites[0].setTexture(m_background_textures[0]);
	m_background_sprites[1].setTexture(m_background_textures[1]);
	m_background_sprites[2].setTexture(m_background_textures[2]);
	m_background_sprites[3].setTexture(m_background_textures[3]);


	m_building_textures.resize(4);

	if (!m_building_textures[0].loadFromFile("Resources/images/1111.png")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	if (!m_building_textures[1].loadFromFile("Resources/images/Top.png")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	if (!m_building_textures[2].loadFromFile("Resources/images/buttom.png")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	if (!m_building_textures[3].loadFromFile("Resources/images/Top.png")) { LOG_ERROR("texture konnte nicht geladen werden"); }

	m_map = std::vector(1, std::vector(height, std::vector(width, Utils::Cell::NOTHING)));
	m_EntityMap = std::vector(1, std::vector(height, std::vector<std::shared_ptr<Entity>>(width)));

	texture.create(window.getSize().x,window.getSize().y);
	
	LOG_DEBUG("m_map size : {}  ; [0] size: {} ; [0][0] size :{}", m_map.size(), m_map[0].size(), m_map[0][0].size());
}

void Game::render_map(glm::vec3 player_pos, sf::RenderTarget& render_target)
{
	//Utils::ScopedTimer ttt("render_map funktion");
	player_pos = round(player_pos / 135.0f);

	constexpr int rendersizex = 11;
	constexpr int rendersizey = 7;

	for (int i = static_cast<int>(player_pos.x) - rendersizex; i < static_cast<int>(player_pos.x) + rendersizex; i++)
	{
		for (int j = static_cast<int>(player_pos.y) - rendersizey; j < static_cast<int>(player_pos.y) + rendersizey; j++)
		{
			if (Utils::is_valid({ i,j,0.0f }))
			{
				m_background_sprites[m_tiles[i][j][0]].setPosition(static_cast<float>(i) * BACKGROUND_WIDTH, static_cast<float>(j) * BACKGROUND_HEIGHT);
				render_target.draw(m_background_sprites[m_tiles[i][j][0]]);
			}
		}
	}
}
void Game::render_tower(sf::RenderTarget& render_target) 
{
	sf::Sprite drawable;
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			switch (m_map[0][j][i])
			{
			case Utils::Cell::WALL:
			{

				drawable.setTexture(m_building_textures[0]);
				drawable.setPosition(i * 135.0f
					, j * 135.0f);
				render_target.draw(drawable);
			}
			break;
			case Utils::Cell::TURRET: //fallthrough
			{
		//		drawable.setTexture(m_building_textures[2]);
		//		drawable.setPosition(i * 135.0f
		//			, j * 135.0f);
		//		m_window.draw(drawable);

		//		drawable.setTexture(m_building_textures[1]);
		//		drawable.setPosition(i * 135.0f
		//			, j * 135.0f);

		//		//drawable.setOrigin( 135.0f / 2.0f, 135.0f / 2.0f);
		//		//drawable.setRotation(45.0f);
		//		m_window.draw(drawable);
		//		//drawable.setRotation(0.0f);
		///*		drawable.setRotation(0.0f);
		//		drawable.setOrigin(0,0);*/


			}
			break;
			case Utils::Cell::NOTHING:
			case Utils::Cell::STAIR:
				break;
			}
		}
	}

}
void Game::run_game(int)
{
	m_sounds.add_group("player");
	m_sounds.add_group("music");
	m_sounds.load_buffer("resources/Sounds/Heilung.mp3", false,"player");
	m_sounds.load_buffer("resources/Sounds/Error.mp3", false,"player");
	m_sounds.load_buffer("resources/Sounds/Hitmarker.wav", false,"player");
	m_sounds.load_buffer("resources/Sounds/Lademusik.mp3", true,"music");
	m_sounds.set_volume(50, -1);
	m_sounds.set_volume(50, 0);
	m_sounds.set_volume(50, 1);

	m_sounds.add_sound("music", 0);
	std::shared_ptr<Player> p = std::make_shared<Player>();

	Camera window_camera(&m_window, p.get());
	Camera texture_camera(&texture, p.get());
	sf::Clock deltaClock;
	Utils::Timer delta_timer;

	Utils::Pathfinding::Init(p, m_map);
	Utils::Pathfinding* pa = Utils::Pathfinding::get_instance();

	bool right_click = false;
	bool left_click = false;

	EnemyManager ma;
	MainBuilding mb;
	healthbar hb{};
	BuildSystem buildsystem;


	m_tiles = erstelle_map();

	m_window.clear();
	render_map(p->get_pos(),m_window);
	m_window.display();

	Utils::Cell selected = Utils::Cell::NOTHING;

	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Tower>> towers;

	bool first_run = true;
	float lautstarke[3] = { 50.0f,50.0f,50.0f };
	bool paused = false;
	bool should_do_dockspace = true;
	bool lautstaerke_UwU{false};
	while (m_window.isOpen() && m_open)
	{
	
		EnemyManager::set_updated_tower(false);
		EnemyManager::set_player_moving(false);
		float deltatime = delta_timer.Elapsed();
		delta_timer.Reset();
		sf::Event event{};

		while (m_window.pollEvent(event)) //Hier werden alle moeglichen Events wie tasten und so weiter gehandled
		{
			ImGui::SFML::ProcessEvent(m_window, event);//Imgui Funktion die die Events handled fuer imgui
			
			switch (event.type)
			{
			case sf::Event::Resized:
				texture.create(event.size.width, event.size.height);
				break;
			case sf::Event::MouseButtonReleased://fallthrough
			case sf::Event::MouseButtonPressed:
			{
				bool down = event.type == sf::Event::MouseButtonPressed;
				if (event.mouseButton.button == sf::Mouse::Button::Left)
					left_click = down;
				if (event.mouseButton.button == sf::Mouse::Button::Right)
					right_click = down;
			}
				break;


			case sf::Event::KeyPressed: //TODO: nicht alles hier machen bitte und logik weiter unten machen
				if (event.key.code == sf::Keyboard::Key::Escape) 
				{
					/*m_sounds.pause_all(false);
					m_open = showpausemenu();
					m_sounds.play_all();*/
					m_open = false;
				}

				break;
			case sf::Event::GainedFocus: //fallthrough
			case sf::Event::LostFocus:
				paused = event.type == sf::Event::LostFocus;
				break;
			case sf::Event::Closed:
				m_window.close();
				break;
			default:
				break;
			}
		}
		ImGui::SFML::Update(m_window, deltaClock.restart());//Imgui funktion damit alles geupdatet wird
		if (should_do_dockspace)
			ImGui::DockSpaceOverViewport();


		if (!paused)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
				ma.add_enemy();
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))  // nur zum debuggen
			//{
			//	m_sounds.add_sound("player", 2);
			//	new Projectile(p->get_pos(), glm::vec3(p->get_movement_speed().x * 2.5, p->get_movement_speed().y * 2.5, 0), 180, 0.1, 5);
			//}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) //Depression.exe 
			{
				m_sounds.add_sound("player", 1);
				hb.damage_input(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			{
				m_sounds.add_sound("player", 0);
				hb.regeneration(1);
			}
		}

		if(paused)
		{
			m_sounds.pause_all(true);
		}
		else
			m_sounds.play_all();

		buildsystem.display();
		sf::Vector2f temp;

		if (should_do_dockspace)
		{
	
			//if (ImGui::BeginMainMenuBar())
			//{
			//	if (ImGui::BeginMenu("File"))
			//	{
			//		if (ImGui::BeginMenu("Sounds bitte UwU"))
			//		{
	
			//			ImGui::EndMenu();
			//		}
			//		ImGui::EndMenu();
			//	}
			//	if (ImGui::BeginMenu("Edit"))
			//	{
			//		if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			//		if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			//		ImGui::Separator();
			//		if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			//		if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			//		if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			//		ImGui::EndMenu();
			//	}
			//	ImGui::EndMainMenuBar();
			//}
			ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);

			ImGui::PushItemWidth(ImGui::GetFontSize() * -12);


			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Menu"))
				{
					if (ImGui::MenuItem("MenuItem")) {}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Examples"))
				{
					if (ImGui::MenuItem("MenuItem")) {}
					ImGui::EndMenu();
				}
				//if (ImGui::MenuItem("MenuItem")) {} // You can also use MenuItem() inside a menu bar!
				if (ImGui::BeginMenu("Tools"))
				{
					if (ImGui::MenuItem("MenuItem")) 
					{

					}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}



			ImVec2 content_size = ImGui::GetContentRegionAvail();

			texture.create(content_size.x, content_size.y);
			texture_camera.set_RenderTarget(&texture);
		}
		if (m_window.hasFocus())//Spiel logik sollte hier rein
		{
			Utils::Timer logic_timer;
			Projectile::update_all(deltatime);

			

			p->update(deltatime);
			window_camera.move_cam_to_player();
			texture_camera.move_cam_to_player();

			if (should_do_dockspace) 
			{
				temp = texture.mapPixelToCoords(sf::Mouse::getPosition(m_window));
				ImVec2 imvec2 = ImGui::GetCursorScreenPos();
				temp = { temp.x - imvec2.x ,temp.y - imvec2.y };
				
			}
			else
			{
				temp = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
			}


			glm::vec3 mouse_pos = glm::vec3{ temp.x,temp.y,0.0f};



			buildsystem(left_click, right_click, should_do_dockspace, m_map, entities, towers,mouse_pos);

			if (should_do_dockspace) {
				ImGui::PopItemWidth();
				ImGui::End();
			}
			p->shoot(deltatime, m_sounds, mouse_pos);
	
			// ReSharper disable once CppUseRangeAlgorithm
			std::for_each(/*std::execution::par,*/ towers.begin(), towers.end(),
			[&ma, &deltatime](std::shared_ptr<Tower>& tower)
			{
			    tower->fire(ma, deltatime);
			});


	

			if (first_run == true || EnemyManager::should_update() == true)
			{
				pa->calculate_paths(towers);
			}
			ma.update(deltatime);
		
			m_sounds.cleanup(false);

			for (auto it = towers.begin(); it != towers.end();)
			{
				if ((*it)->get_hp() <= 0)
				{
					it->reset();
					it = towers.erase(it);
					EnemyManager::set_updated_tower(true);
				}
				else
					++it;
			}

			for (auto it = entities.begin(); it != entities.end();)
			{
				if ((*it)->get_hp() <= 0)
				{
					const glm::ivec3 cell_pos = (*it)->get_pos() / 135.0f;
					m_map[0][cell_pos.y][cell_pos.x] = Utils::Cell::NOTHING;
					m_EntityMap[0][cell_pos.y][cell_pos.x].reset();
					it = entities.erase(it);
					EnemyManager::set_updated_tower(true);
				}
				else
					++it;
			}

				if (!hb.alive())
			{
				m_open = false;
			}
			ma.naive_enemy_killer();

			ImGui::Begin("DEBUG WINDOW");
			ImGui::TextWrapped("Game logic: MS: %f ", logic_timer.Elapsed() * 1000.0f);
			ImGui::TextWrapped("temp x:%f y:%f", temp.x, temp.y);
			ImGui::TextWrapped("mouse_pos x:%f y:%f z:%f", mouse_pos.x, mouse_pos.y, mouse_pos.z);
			glm::vec3 tt = mouse_pos / 135.0f;
			ImGui::TextWrapped("cell_mouse_pos x:%f y:%f z:%f", tt.x, tt.y, tt.z);
			ImGui::End();
		}
		else if(should_do_dockspace)
		{
			ImGui::PopItemWidth();
			ImGui::End();
		}

		{//Debug Fenster
			ImGui::Begin("DEBUG WINDOW");
			ImGui::TextWrapped("MS: %f FPS: %2.2f", deltatime * 1000.0f, 1.0f / deltatime);
			ImGui::TextWrapped("amount of enemies: %llu", ma.get_enemies().size());
			if(ImGui::Button("should do docking"))
			{
				should_do_dockspace = !should_do_dockspace;
			}

			if (paused)
				ImGui::TextWrapped("paused");
			else
				ImGui::TextWrapped("not paused");

			ImGui::SliderFloat("Allgemein", lautstarke, 0, 100);
			ImGui::SliderFloat("Player", &lautstarke[1], 0, 100);
			ImGui::SliderFloat("Musik", &lautstarke[2], 0, 100);
			m_sounds.set_volume(lautstarke[0], -1);
			m_sounds.set_volume(lautstarke[1], 0);
			m_sounds.set_volume(lautstarke[2], 1);

			ImGui::End();
		}

		{//Rendern (Bitte keine als zu große logik ab hier)

			//hier ist die render order
			m_window.clear();//das momentane fenster wird gecleared

			render_map(p->get_pos(),m_window); //als erstes wird der Boden gerendert (weil der immer ganz unten sein sollte)
			mb.main_sprite(m_window);
			for (auto& tower : towers)
			{
				//texture.draw(*tower);
				tower->drawtower(m_window);
			}
			render_tower(m_window);
			ma.draw(m_window);
			m_window.draw(*p);
			Projectile::draw_all_projectiles(m_window);
			hb.draw_healthbar(m_window, *p);
			if (should_do_dockspace) {
				texture.clear();
				render_map(p->get_pos(), texture); //als erstes wird der Boden gerendert (weil der immer ganz unten sein sollte)
				mb.main_sprite(texture);
				for (auto& tower : towers)
				{
					//texture.draw(*tower);
					tower->drawtower(texture);
				}
				render_tower(texture);
				ma.draw(texture);
				texture.draw(*p);
				Projectile::draw_all_projectiles(texture);
				hb.draw_healthbar(texture, *p);
				texture.display();

				ImGui::Begin("Viewport");
				ImGui::Image(texture);
				ImGui::End();
			}

			ImGui::SFML::Render(m_window); //zu guter letzt kommt imgui (die fenster wie Debug und so)
			
			m_window.display();
		}
		first_run = false;
	}
	
	m_sounds.clear_all();
	m_tiles.clear();
	m_open = true;
	window_camera.move_to_default();
	texture_camera.move_to_default();
	Utils::Pathfinding::Delete();
	pa = nullptr;

	for (auto& i : m_map)
	{
		for (auto& j : i)
		{
			for (auto& k : j)
			{
				k = Utils::Cell::NOTHING;
			}
		}
	}



}

void Game::erstelle_game(sf::RenderWindow& i_window)
{
	if (!s_game)
		s_game = new Game(i_window);
}

Game* Game::get_game()
{
	return s_game;
}

std::vector<std::vector<std::vector<std::shared_ptr<Entity>>>>& Game::getEntityMap()
{
	return (s_game->m_EntityMap);
}

void Game::set_map(const Utils::Cell& cell, int x, int y, int z) {
	if (
		z < m_map.size() && z >= 0 &&
		y < m_map[z].size() && y >= 0 &&
		x < m_map[z][y].size() && x >= 0
		)
		m_map[z][y][x] = cell;
	else
		LOG_ERROR("index [{}][{}][{}] is not valid", z, y, x);
}
std::vector<std::vector<std::vector<Utils::Cell>>>& Game::get_map() {
	return m_map;
}

