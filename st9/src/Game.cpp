#include "Game.h"

#include <complex>
#include <SFML/Graphics.hpp>
#include "Utils/Utils.h"
#include <imgui.h>
#include "Camera.h"
#include "imgui-SFML.h"
#include "Player.h"
#include "Enemymanager.h"

constexpr int BACKGROUND_HEIGHT = 135;
constexpr int BACKGROUND_WIDTH = 135;

constexpr int height = 20;
constexpr int width = 40;

std::vector<std::vector<std::array<uint8_t, 2>>> erstelleMap()
{
	std::vector<std::vector<std::array<uint8_t, 2>>> KARTE;
	std::array<uint8_t, 2> single_cell = { 0,0 };
	for (int i = 0; i < width; i++)
	{
		std::vector<std::array<uint8_t, 2>> inner_map;
		for (int j = 0; j < height; j++)
		{
			single_cell[0] = Utils::Random::UInt(0, 3);
			inner_map.emplace_back(single_cell);

		}
		KARTE.emplace_back(inner_map);
	}
	return KARTE;
}

Game::Game(sf::RenderWindow& window) :m_window(window)
{
	//window.setFramerateLimit(2);
	m_background_textures.resize(4);

	if (!m_background_textures[0].loadFromFile("Resources/Background1.jpg"))throw std::exception("Fehler");
	if (!m_background_textures[1].loadFromFile("Resources/Background2.jpg"))throw std::exception("Fehler");
	if (!m_background_textures[2].loadFromFile("Resources/Background3.jpg"))throw std::exception("Fehler");
	if (!m_background_textures[3].loadFromFile("Resources/Background4.jpg"))throw std::exception("Fehler");

	m_background_sprites.resize(4);

	m_background_sprites[0].setTexture(m_background_textures[0]);
	m_background_sprites[1].setTexture(m_background_textures[1]);
	m_background_sprites[2].setTexture(m_background_textures[2]);
	m_background_sprites[3].setTexture(m_background_textures[3]);
	m_map = std::vector(1, std::vector(height, std::vector(width, Utils::Cell::NOTHING)));

	LOG_DEBUG("m_map size : {}  ; [0] size: {} ; [0][0] size :{}",m_map.size(), m_map[0].size(), m_map[0][0].size());
}

void Game::render_map()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			m_background_sprites[m_tiles[i][j][0]].setPosition(i * BACKGROUND_WIDTH, j * BACKGROUND_HEIGHT);
			m_window.draw(m_background_sprites[m_tiles[i][j][0]]);
		}
	}


}

void Game::render_tower()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			
			if (m_map[0][j][i] != Utils::Cell::NOTHING) {
				sf::RectangleShape rect (sf::Vector2<float>{120,120});
				rect.setPosition(i * 135, j * 135);
				
				m_window.draw(rect);
			}
		}
	}

}
void Game::run_game(int)
{
	std::shared_ptr<Player> p = std::make_shared<Player>();
	Camera c(&m_window, p.get());
	sf::Clock deltaClock;
	Utils::Timer player_timer;
	Utils::Timer enemymanager_timer;
	Utils::Timer frame_timer;

	Utils::Pathfinding::Init(p, m_map);
	Utils::Pathfinding* pa = Utils::Pathfinding::get_instance();

	Enemymanager ma;
	m_tiles = erstelleMap();
	m_window.clear();
	render_map();
	m_window.display();
	bool epilepsy = false;

	while (m_window.isOpen() && m_open)
	{
		sf::Event event{};
		while (m_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(m_window, event);
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Key::Escape)
					m_open = false;
				if (event.key.code == sf::Keyboard::Key::E)
					ma.add_enemy();
				break;

			case sf::Event::Closed:
				m_window.close();
				break;
			default:
				break;
			}
		}
		LOG_DEBUG("amount of enemies: {}",ma.get_enemies().size());
		ImGui::SFML::Update(m_window, deltaClock.restart());
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		{
			sf::Vector2f temp(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
			glm::vec3 mouse_pos = { temp.x / 135.0f, temp.y / 135.0f, 0 };
			if(Utils::Pathfinding::get_instance()->is_valid(mouse_pos))
			{
				m_map[0][mouse_pos.y][mouse_pos.x] = Utils::Cell::WALL;

			}
		}
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right) )
		{
			sf::Vector2f temp(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
			glm::vec3 mouse_pos = { temp.x / 135.0f, temp.y / 135.0f, 0 };
			if(Utils::Pathfinding::get_instance()->is_valid(mouse_pos))
			{
				m_map[0][mouse_pos.y][mouse_pos.x] = Utils::Cell::NOTHING;

			}
		}

		p->update(player_timer.Elapsed());

		player_timer.Reset();

		ma.update(enemymanager_timer.Elapsed());
		enemymanager_timer.Reset();

		{
			ImGui::Begin("DEBUG WINDOW");

			ImGui::TextWrapped("MS: %f FPS: %2.2f", frame_timer.ElapsedMillis(), 1/frame_timer.Elapsed());
			frame_timer.Reset();

			ImGui::End();
		}


		c.move_cam_to_player();
		m_window.clear();

		render_map();
		render_tower();
		ma.draw(m_window);
		m_window.draw(*p);
		

		ImGui::SFML::Render(m_window); // muss als letztes gezeichnet werden wegen z achse (damit es ganz oben ist)

		m_window.display();
	}
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

void Game::set_map(Utils::Cell& cell, int x, int y, int z) {
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

