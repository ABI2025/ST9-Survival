#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include "Utils/Log.h"
#include "Utils/Utils.h"

class BuildSystem
{

   
    std::vector<sf::Texture> m_textures;
    std::vector<sf::Sprite> m_sprites;
    Utils::Cell m_selected;
public:

    BuildSystem() : m_selected(Utils::Cell::NOTHING)
    {
        m_textures.resize(4);
        m_textures[0].loadFromFile("resources/images/charakter_HL.png");
        m_textures[1].loadFromFile("resources/images/top.png");
        m_textures[2].loadFromFile("resources/images/top.png");
        m_textures[3].loadFromFile("resources/images/1111.png");
        m_sprites.resize(4);
        m_sprites[0].setTexture(m_textures[0]);
        m_sprites[1].setTexture(m_textures[1]);
        m_sprites[2].setTexture(m_textures[2]);
        m_sprites[3].setTexture(m_textures[3]);
    }


    Utils::Cell display()
	{
        ImGui::Begin("test");
        for(int i = 0; i < m_sprites.size(); i++)
        {
            std::string t = "test" + std::to_string(i);
            if (ImGui::ImageButton(t.c_str(), m_sprites[i], {135.0f,135.0f}))
            {
                //LOG_INFO("it works ig");
                m_selected = static_cast<Utils::Cell>(i);
            }
        }
        ImGui::End();
        return m_selected;
    }
};
