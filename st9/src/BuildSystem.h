#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Utils/Utils.h"


class BuildSystem
{
	std::vector<sf::Texture> m_texture_textures;
	std::vector<sf::Sprite> m_texture_sprites;
	sf::RenderTexture m_texture[5];
	std::vector<sf::Texture> m_textures;
	std::vector<sf::Sprite> m_sprites;
	Utils::Cell m_selected;
	std::map<int, double> m_costs;
	int m_id{ -1 };

	inline static BuildSystem* s_instance;

	BuildSystem();
public:

	static BuildSystem* get_instance();

	static void delete_instance();

	Utils::Cell display();

	void operator()(bool left_click, bool right_click, bool should_do_docking,
		std::vector<std::vector<std::vector<Utils::Cell>>>& map,
		std::vector<std::shared_ptr<Entity>>& entities,
		std::vector<std::shared_ptr<Tower>>& towers,
		glm::vec3 mouse_pos,
		glm::vec3 mainbuilding_pos
		
		) const;
};
