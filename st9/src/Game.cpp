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
#include "Projektil.h" //können wir später löschen, ist nur zum debuggen hier
#include "Sounds.h"
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

	LOG_DEBUG("m_map size : {}  ; [0] size: {} ; [0][0] size :{}", m_map.size(), m_map[0].size(), m_map[0][0].size());
}

void Game::render_map(glm::vec3 player_pos)
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
				m_window.draw(m_background_sprites[m_tiles[i][j][0]]);
			}
		}
	}
}

void Game::render_tower() const
{
	sf::Sprite sprite;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			switch (m_map[0][j][i])
			{
			case Utils::Cell::WALL:
			{

				sprite.setTexture(m_building_textures[0]);
				sprite.setPosition(i * 135.0f
					, j * 135.0f);
				m_window.draw(sprite);
			}
			break;
			case Utils::Cell::TURRET: //fallthrough
			case Utils::Cell::DEFENSE:
			{
				sprite.setTexture(m_building_textures[2]);
				sprite.setPosition(i * 135.0f
					, j * 135.0f);
				m_window.draw(sprite);

				sprite.setTexture(m_building_textures[1]);
				sprite.setPosition(i * 135.0f
					, j * 135.0f);
				m_window.draw(sprite);
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
	static_assert(height <= 20);
	static_assert(width <= 40);
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

	Camera c(&m_window, p.get());
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
	render_map(p->get_pos());
	m_window.display();

	Utils::Cell selected = Utils::Cell::NOTHING;

	std::vector<glm::ivec3> towers;

	bool first_run = true;
	float lautstarke[3] = { 50.0f,50.0f,50.0f };
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
			//if (m_window.hasFocus())//falls das spiel nicht 
			//{
			
				switch (event.type)
				{

				case sf::Event::MouseButtonReleased: //Warum kein fallthrough und einfach left_click != left_click wegen eines Bug
					if (event.mouseButton.button == sf::Mouse::Button::Left)
						left_click = false;
					if (event.mouseButton.button == sf::Mouse::Button::Right)
						right_click = false;
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Button::Left)
						left_click = true;
					if (event.mouseButton.button == sf::Mouse::Button::Right)
						right_click = true;
					break;


				case sf::Event::KeyPressed: //TODO: nicht alles hier machen bitte und logik weiter unten machen
					if (event.key.code == sf::Keyboard::Key::Escape) 
					{
						/*m_sounds.pause_all(false);
						m_open = showpausemenu();
						m_sounds.play_all();*/
						m_open = false;
					}
					if (event.key.code == sf::Keyboard::Key::E)
						ma.add_enemy();
					if (event.key.code == sf::Keyboard::Key::F)  // nur zum debuggen
					{
						m_sounds.add_sound("player", 2);
						new Projectile(p->get_pos(), glm::vec3(p->get_movement_speed().x * 2.5, p->get_movement_speed().y * 2.5, 0), 180, 0.1, 5);
					}
					if (event.key.code == sf::Keyboard::Key::L) //Depression.exe 
					{
						m_sounds.add_sound("player",1);
						hb.damage_input(1);
					}
					if (event.key.code == sf::Keyboard::Key::R)
					{
						m_sounds.add_sound("player", 0);
						hb.regeneration(1);
					}
					break;
				case sf::Event::LostFocus://bitte pausenbildschirm 

					break;
				case sf::Event::Closed:
					m_window.close();
					break;
				default:
					break;
				}
			//}

		}
		ImGui::SFML::Update(m_window, deltaClock.restart());//Imgui funktion damit alles geupdatet wird

		{//Buildsystem
			selected = buildsystem.display();

			if (left_click && m_window.hasFocus() && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
			{
				sf::Vector2f temp(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

				glm::ivec3 mouse_pos = { temp.x / 135.0f, temp.y / 135.0f, 0 };

				if (pa->is_valid(mouse_pos) && selected != Utils::Cell::NOTHING && m_map[0][mouse_pos.y][mouse_pos.x] != selected)
				{
					//set_map(selected, static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y), 0);
					if(selected == Utils::Cell::TURRET || selected == Utils::Cell::DEFENSE)
						towers.emplace_back(mouse_pos);
					if((m_map[0][mouse_pos.y][mouse_pos.x] == Utils::Cell::DEFENSE || m_map[0][mouse_pos.y][mouse_pos.x] == Utils::Cell::TURRET)
						&& (selected != Utils::Cell::TURRET && selected != Utils::Cell::DEFENSE))
					{
						for (auto it = towers.begin(); it != towers.end();)
						{
							if ((*it).x == mouse_pos.x && (*it).y == mouse_pos.y)
							{
								LOG_INFO("success 2");
								it = towers.erase(it);
							}
							else 
							{
								++it;
							}
						}
					}

					m_map[0][mouse_pos.y][mouse_pos.x] = selected;
					EnemyManager::set_updated_tower(true);
				}
			}
			if (right_click && m_window.hasFocus() && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
			{
				sf::Vector2f temp(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
				glm::ivec3 mouse_pos = { temp.x / 135.0f, temp.y / 135.0f, 0 };
				if (pa->is_valid(mouse_pos) && selected != Utils::Cell::NOTHING && m_map[0][mouse_pos.y][mouse_pos.x] != Utils::Cell::NOTHING)
				{
					//set_map(Utils::Cell::NOTHING, static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y), 0);
					if(m_map[0][mouse_pos.y][mouse_pos.x] == Utils::Cell::DEFENSE || m_map[0][mouse_pos.y][mouse_pos.x] == Utils::Cell::TURRET)
					{
						for(auto it = towers.begin(); it != towers.end();)
						{
							if ((*it).x == mouse_pos.x && (*it).y == mouse_pos.y)
							{
								it = towers.erase(it);
							}
							else
							{
								++it;
							}
						}
					}

					m_map[0][mouse_pos.y][mouse_pos.x] = Utils::Cell::NOTHING;
					EnemyManager::set_updated_tower(true);
				}
			}
		}


		if (m_window.hasFocus())//Spiel logik sollte hier rein
		{
			Utils::Timer logic_timer;
			
			p->update(deltatime);
			if (first_run == true || EnemyManager::should_update() == true)
			{
				pa->calculate_paths(towers);
			}
			ma.update(deltatime);
			ImGui::Begin("DEBUG WINDOW");
			ImGui::TextWrapped("Game logic: MS: %f ", logic_timer.Elapsed() * 1000.0f);
			ImGui::End();
			m_sounds.cleanup(false);
		}

		{//Debug Fenster
			ImGui::Begin("DEBUG WINDOW");

			ImGui::TextWrapped("MS: %f FPS: %2.2f", deltatime * 1000.0f, 1.0f / deltatime);
			ImGui::TextWrapped("amount of enemies: %llu", ma.get_enemies().size());
			if (ImGui::Button("fix lc/right click"))
			{
				left_click = false;
				right_click = false;
			}
			ImGui::SliderFloat("Allgemein", lautstarke, 0, 100);
			ImGui::SliderFloat("Player", &lautstarke[1], 0, 100);
			ImGui::SliderFloat("Musik", &lautstarke[2], 0, 100);
			m_sounds.set_volume(lautstarke[0], -1);
			m_sounds.set_volume(lautstarke[1], 0);
			m_sounds.set_volume(lautstarke[2], 1);
			ImGui::End();
		}

		if (!hb.alive()) 
		{
			m_open = false;
		}
		ma.naive_enemy_killer();

		c.move_cam_to_player();

		{//Rendern (Bitte keine als zu große logik ab hier)

			//hier ist die render order
			m_window.clear();//das momentane fenster wird gecleared

			render_map(p->get_pos()); //als erstes wird der Boden gerendert (weil der immer ganz unten sein sollte)
			mb.main_sprite(m_window); 
			render_tower();
			ma.draw(m_window);
			m_window.draw(*p);
			Projectile::draw_all_projectiles(m_window);
			hb.draw_healthbar(m_window, *p);
			ImGui::SFML::Render(m_window); //zu guter letzt kommt imgui (die fenster wie Debug und so)

			m_window.display();
		}
		first_run = false;
	}

	m_sounds.clear_all();
	m_tiles.clear();
	m_open = true;
	c.move_to_default();
	Utils::Pathfinding::Delete();
	pa = nullptr;

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

