#include "Game.h"
#include "healthbar.h"
#include <complex>
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <imgui.h>
#include <SFML/Audio.hpp>

#include "BuildSystem.h"
#include "BuildSystem.h"
#include "camera.h"
#include "imgui-SFML.h"
#include "entities/Player/Player.h"
#include "entities/EnemyManager.h"
#include "MainBuilding.h"
#include "BuildSystem.h"
#include "imgui_internal.h"
#include "Optionen.h"
#include "projektil.h" //können wir später löschen, ist nur zum debuggen hier // doch jetzt ist es eine kern funktion
#include "Sounds.h"
#include "Tower.h"
#include "Wave.h"
#include "Utils/Timer.h"

constexpr int BACKGROUND_HEIGHT = 135;
constexpr int BACKGROUND_WIDTH = 135;

constexpr int height = 22;
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

Game::Game(sf::RenderWindow& window, Sounds& sounds) :m_window(window), m_sounds(sounds)
{
	//window.setFramerateLimit(2);
	m_background_textures.resize(4);
	m_geld = 1000;
	if (!m_background_textures[0].loadFromFile("Resources/Images/Background1.jpg")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	if (!m_background_textures[1].loadFromFile("Resources/Images/Background2.jpg")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	if (!m_background_textures[2].loadFromFile("Resources/Images/Background3.jpg")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	if (!m_background_textures[3].loadFromFile("Resources/Images/Background4.jpg")) { LOG_ERROR("texture konnte nicht geladen werden"); } // lade background tiles texturen

	m_background_sprites.resize(4);

	m_background_sprites[0].setTexture(m_background_textures[0]);
	m_background_sprites[1].setTexture(m_background_textures[1]);
	m_background_sprites[2].setTexture(m_background_textures[2]);
	m_background_sprites[3].setTexture(m_background_textures[3]);

	m_background_sprites[0].setOrigin(135.0f/2.0f,135.0f/2.0f);
	m_background_sprites[1].setOrigin(135.0f/2.0f,135.0f/2.0f);
	m_background_sprites[2].setOrigin(135.0f/2.0f,135.0f/2.0f);
	m_background_sprites[3].setOrigin(135.0f/2.0f,135.0f/2.0f);

	//m_building_textures.resize(4);

	//if (!m_building_textures[0].loadFromFile("Resources/Images/1111.png")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	//if (!m_building_textures[1].loadFromFile("Resources/Images/Top.png")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	//if (!m_building_textures[2].loadFromFile("Resources/Images/buttom.png")) { LOG_ERROR("texture konnte nicht geladen werden"); }
	//if (!m_building_textures[3].loadFromFile("Resources/Images/Top.png")) { LOG_ERROR("texture konnte nicht geladen werden"); } // Lade building texturen


	m_ui_textures.resize(1);

	if (!m_ui_textures[0].loadFromFile("Resources/Images/v-bucks.png")) { LOG_ERROR("texture konnte nicht geladen werden"); } //lade V-Buck Texture

	m_map = std::vector(1, std::vector(height, std::vector(width, Utils::Cell::NOTHING)));
	m_EntityMap = std::vector(1, std::vector(height, std::vector<std::shared_ptr<Entity>>(width)));

	texture.create(window.getSize().x, window.getSize().y);

	LOG_DEBUG("m_map size : {}  ; [0] size: {} ; [0][0] size :{}", m_map.size(), m_map[0].size(), m_map[0][0].size());
}

void Game::render_map_and_tower(glm::vec3 player_pos, sf::RenderTarget& render_target, float deltatime)
{
	//Utils::ScopedTimer ttt("render_map funktion");
	player_pos = round(player_pos / 135.0f);

	constexpr int rendersizex = 11;
	constexpr int rendersizey = 7;
	if(Optionen::get_instance()->get_should_rotate())
	{
		m_background_sprites[0].rotate(36 * deltatime);
		m_background_sprites[1].rotate(36 * deltatime);
		m_background_sprites[2].rotate(36 * deltatime);
		m_background_sprites[3].rotate(36 * deltatime);
	}
	else
	{
		m_background_sprites[0].setRotation(0);
		m_background_sprites[1].setRotation(0);
		m_background_sprites[2].setRotation(0);
		m_background_sprites[3].setRotation(0);
	}
	for (int i = static_cast<int>(player_pos.x) - rendersizex; i < static_cast<int>(player_pos.x) + rendersizex; i++)
	{
		for (int j = static_cast<int>(player_pos.y) - rendersizey; j < static_cast<int>(player_pos.y) + rendersizey; j++)
		{
			if (Utils::is_valid({ i,j,0.0f }))
			{
				m_background_sprites[m_tiles[i][j][0]].setPosition(static_cast<float>(i) * BACKGROUND_WIDTH + 135.0f/2.0f, static_cast<float>(j) * BACKGROUND_HEIGHT + 135.0f / 2.0f);
				render_target.draw(m_background_sprites[m_tiles[i][j][0]]);

				if (glm::vec2(i, j) != glm::vec2{ 20,10 } && glm::vec2(i, j) != glm::vec2(20, 11) && m_EntityMap[0][j][i]) {
					m_EntityMap[0][j][i]->update(deltatime);
					render_target.draw(*m_EntityMap[0][j][i]);
				}
			}
		}
	}
}

void Game::run_game(int)
{
	Wave::wave_counter = 0;
	m_geld = 1000;
	m_sounds.music(0);
	std::shared_ptr<Player> p = std::make_shared<Player>();
	Optionen* opt = Optionen::get_instance();

	Camera window_camera(&m_window, p.get());
	Camera texture_camera(&texture, p.get());
	sf::Clock deltaClock;
	Utils::Timer delta_timer;

	Utils::Pathfinding::Init(p, m_map);
	Utils::Pathfinding* pa = Utils::Pathfinding::get_instance();

	bool right_click = false;
	bool left_click = false;

	EnemyManager* ma = EnemyManager::get_instance();
	WaveManager wave_manager;
	std::shared_ptr<MainBuilding> mb = std::make_shared<MainBuilding>();
	{
		const glm::vec2 cell_pos = mb->get_pos() / 135.0f;
		m_EntityMap[0][static_cast<int>(cell_pos.y)][static_cast<int>(cell_pos.x)] = mb;
		m_EntityMap[0][static_cast<int>(cell_pos.y) + 1][static_cast<int>(cell_pos.x)] = mb;
		m_map[0][static_cast<int>(cell_pos.y)][static_cast<int>(cell_pos.x)] = Utils::Cell::TURRET;
		m_map[0][static_cast<int>(cell_pos.y) + 1][static_cast<int>(cell_pos.x)] = Utils::Cell::TURRET;
	}
	healthbar::init(p->get_hp());
	healthbar* hb = healthbar::get_instance();
	BuildSystem* buildsystem = BuildSystem::get_instance();


	m_tiles = erstelle_map();

	//m_window.clear();
	//render_map(p->get_pos(), m_window);
	//m_window.display();

	Utils::Cell selected = Utils::Cell::NOTHING;

	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Tower>> towers;

	bool first_run = true;
	bool paused = false;
	bool player_alive = true;
	p->set_pos(mb->get_pos());
	EnemyManager::set_updated_tower(true);
	EnemyManager::set_player_moving(true);
	EnemyManager::set_walls_update(true);
	pa->calculate_paths(towers, mb);
	bool show_option_menu = false;
	constexpr float player_cooldown = 5;
	float player_rem_cooldown = 0.0f;
	constexpr float player_grace = 5;
	float player_rem_grace = 0.0f;
	while (m_window.isOpen() && m_open)
	{

		EnemyManager::set_updated_tower(false);
		EnemyManager::set_player_moving(false);
		EnemyManager::set_walls_update(false);

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

					show_option_menu = true;
					//m_open = false;
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
		if (opt->get_should_do_dockspace())
			ImGui::DockSpaceOverViewport();


		if (paused)
		{
			m_sounds.pause_all(true);
		}
		else
			m_sounds.play_all();

		Utils::Cell temp_cell = buildsystem->display();

		if (opt->get_should_do_dockspace())
		{
			ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
			ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

			ImVec2 content_size = ImGui::GetContentRegionAvail();

			texture.create(static_cast<uint32_t>(content_size.x), static_cast<uint32_t>(content_size.y));
			texture_camera.set_render_target(&texture);
		}
		window_camera.move_cam_to_player();
		texture_camera.move_cam_to_player();
		if (m_window.hasFocus())//Spiel logik sollte hier rein
		{

			sf::Vector2f temp;
			Utils::Timer logic_timer;
			Projectile::update_all(deltatime);

			if (player_alive == false)
			{

				player_rem_cooldown -= deltatime;
				if (player_rem_cooldown <= 0)
				{
					hb->regeneration(21);

					p->set_hp(200);
					p->set_pos(mb->get_pos());
					player_alive = true;
					EnemyManager::set_player_moving(true);
					p->set_is_alive(true);
					player_rem_grace = player_grace;
				}
			}
			else if (player_rem_grace > 0.0)
				player_rem_grace -= deltatime;

			if (!hb->alive() && player_alive)
			{
				p->set_pos(mb->get_pos());
				player_rem_cooldown = player_cooldown;
				player_alive = false;
				EnemyManager::set_player_moving(true);
				p->set_is_alive(false);
			}
			else if (player_alive)
				p->take_damage(5.f * -deltatime);

			p->update_player(deltatime);

			if (opt->get_should_do_dockspace())
			{
				temp = texture.mapPixelToCoords(sf::Mouse::getPosition(m_window));
				ImVec2 imvec2 = ImGui::GetCursorScreenPos();
				temp = { temp.x - imvec2.x ,temp.y - imvec2.y };

			}
			else
			{
				temp = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
			}


			glm::vec3 mouse_pos = glm::vec3{ temp.x,temp.y,0.0f };


			if (player_alive)
				(*buildsystem)(left_click, right_click, opt->get_should_do_dockspace(), m_map, entities, towers, mouse_pos, mb->get_pos());

			std::ranges::sort(towers,
				[&p](const std::shared_ptr<Tower>& tower1, const std::shared_ptr<Tower>& tower2)
				{
					const glm::ivec2 distance_player_tower1 = (p->get_pos() - tower1->get_pos());
					const glm::ivec2 distance_player_tower2 = (p->get_pos() - tower2->get_pos());
					const int manhattan_distance_player_to_tower1 = abs(distance_player_tower1.x) + abs(distance_player_tower1.y);
					const int manhattan_distance_player_to_tower2 = abs(distance_player_tower2.x) + abs(distance_player_tower2.y);
					return manhattan_distance_player_to_tower1 < manhattan_distance_player_to_tower2;
				});

			if (opt->get_should_do_dockspace()) {
				ImGui::PopItemWidth();
				ImGui::End();
			}
			p->shoot(deltatime, m_sounds, mouse_pos);

			// ReSharper disable once CppUseRangeAlgorithm
			std::for_each(/*std::execution::par,*/ towers.begin(), towers.end(),
				[this, &ma, &deltatime](const std::shared_ptr<Tower>& tower)
				{
					tower->fire(*ma, m_sounds, deltatime);
				});


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
					if (m_map[0][cell_pos.y][cell_pos.x] == Utils::Cell::TURRET)
						EnemyManager::set_updated_tower(true);
					else if (m_map[0][cell_pos.y][cell_pos.x] == Utils::Cell::WALL)
						EnemyManager::set_walls_update(true);
					m_map[0][cell_pos.y][cell_pos.x] = Utils::Cell::NOTHING;
					m_EntityMap[0][cell_pos.y][cell_pos.x].reset();
					it = entities.erase(it);
				}
				else
					++it;
			}
			mb->update(deltatime);
			if (first_run == true || EnemyManager::should_update() == true)
			{
				pa->calculate_paths(towers, mb);
			}
			ma->update(deltatime);
			if (player_rem_grace <= 0 && player_alive)
				p->do_damage_calc();

			wave_manager.spawnening(ma, deltatime);

			m_sounds.cleanup();
			m_sounds.music(deltatime);


			if (mb->get_hp() <= 0)
			{
				m_open = false;
			}
			ma->naive_enemy_killer();


		}
		else if (opt->get_should_do_dockspace())
		{
			ImGui::PopItemWidth();
			ImGui::End();
		}

		{//Spiel Info Fenster
			ImGui::Begin("Spiel Infos");
			//ImGui::TextWrapped("MS: %f\nFPS: %2.2f", deltatime * 1000.0f, 1.0f / deltatime); //zum fps Debuggen 
			ImGui::TextWrapped("Menge An Lebenden Gegnern: %llu", ma->get_enemies().size());
			ImGui::TextWrapped("V-Bucks %f", m_geld);
			if (!player_alive)
				ImGui::TextWrapped("Wiederbelebungs Zeit %f", player_rem_cooldown);
			ImGui::SameLine();
			sf::Sprite temp_drawable(m_ui_textures[0]);
			temp_drawable.setScale(0.1f, 0.1f);
			ImGui::Image(temp_drawable);
			ImGui::End();
		}

		{//RENDERN


			m_window.clear();//das momentane fenster wird gecleared

			if (opt->get_should_do_dockspace()) {
				texture.clear();
				render_map_and_tower(p->get_pos(), texture, deltatime); //als erstes wird der Boden gerendert (weil der immer ganz unten sein sollte)
				texture.draw(*mb);
				ma->draw(texture);

				if (p->get_hp() > 0)
				{
					texture.draw(*p);
				}
				Projectile::draw_all_projectiles(texture);
				hb->draw_healthbar(texture, *p);
				texture.display();
				ImGui::Begin("Viewport");
				ImGui::Image(texture);
				ImGui::End();
			}
			else
			{
				render_map_and_tower(p->get_pos(), m_window, deltatime); //als erstes wird der Boden gerendert (weil der immer ganz unten sein sollte)
				m_window.draw(*mb);
				ma->draw(m_window);
				if (p->get_hp() > 0)
				{
					m_window.draw(*p);
				}
				Projectile::draw_all_projectiles(m_window);
				hb->draw_healthbar(m_window, *p);

				hb->draw_healthbar(m_window, *p);
			}

			ImGui::SFML::Render(m_window); //zu guter letzt kommt imgui (die fenster wie Debug und so)

			m_window.display();

			if (show_option_menu)
			{
				m_open = opt->optionen_exe(m_window, true);
				delta_timer.Reset();
				deltaClock.restart();
				show_option_menu = false;
			}

		}
		first_run = false;
	}


	//cleanup
	m_tiles.clear();
	m_open = true;

	if (EnemyManager::get_enemies_killed() > EnemyManager::get_highscore())
	{
		bool show_highscore = true;

		while (m_window.isOpen() && show_highscore)
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
			ImGui::Begin("HIGHSCORE", &show_highscore);


			ImGui::Text("NEW HIGHSCORE");
			ImGui::Text("new: %lld", EnemyManager::get_enemies_killed());
			ImGui::Text("old: %lld", EnemyManager::get_highscore());


			if (ImGui::Button("Close"))
			{
				show_highscore = false;
			}

			ImGui::End();

			ImGui::SFML::Render(m_window);
			m_window.display();
		}
	}

	EnemyManager::delete_instance();
	ma = nullptr;
	window_camera.move_to_default();
	texture_camera.move_to_default();
	Utils::Pathfinding::Delete();
	pa = nullptr;
	BuildSystem::delete_instance();
	buildsystem = nullptr;
	m_sounds.delete_sounds();
	healthbar::delete_instance();
	for (int i = 0; i < m_map.size(); i++)
	{
		for (int j = 0; j < m_map[i].size(); j++)
		{
			for (int k = 0; k < m_map[i][j].size(); k++)
			{
				m_map[i][j][k] = Utils::Cell::NOTHING;
				m_EntityMap[i][j][k].reset();
			}
		}
	}
}

void Game::add_geld(const double i_geld)
{
	m_geld += i_geld;
}

void Game::erstelle_game(sf::RenderWindow& i_window, Sounds& sounds)
{
	if (!s_game)
		s_game = new Game(i_window, sounds);
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

