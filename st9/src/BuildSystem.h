#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Utils/Utils.h"


class BuildSystem
{
    std::vector<sf::Texture> m_texture_textures;
    std::vector<sf::Sprite> m_texture_sprites;
    sf::RenderTexture m_texture;
    std::vector<sf::Texture> m_textures;
    std::vector<sf::Sprite> m_sprites;
    Utils::Cell m_selected;
    int m_id{-1};
public:

    BuildSystem();

    Utils::Cell display();

    void operator()(bool left_click, bool right_click, bool should_do_docking, std::vector<std::vector<std::vector<Utils::Cell>>>& map, std::vector<Tower>& towers , glm::ivec3 mouse_pos) const;
};
