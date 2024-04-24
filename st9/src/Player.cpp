#include "Player.h"
#include "Utils/Log.h"
#include <iostream>

#include "EnemyManager.h"
#include "imgui.h"
#include "imgui-sfml.h"

Player::Player()
    : Entity()

{
    m_pos = { 720, 720, 0 };
    cell_pos = m_pos / 135.0f;
    prev_cell_pos = m_pos / 135.0f;
    m_textures.resize(2);
    for (auto& t : m_textures)
    {
        t.resize(3);
        for (auto& tt : t)
        {
            tt.resize(3);
        }
    }

    m_textures[0][0][0].loadFromFile("Resources/images/charakter_L.png");
    m_textures[0][0][1].loadFromFile("Resources/images/charakter_L1.png");
    m_textures[0][0][2].loadFromFile("Resources/images/charakter_L2.png");

    m_textures[0][1][0].loadFromFile("Resources/images/charakter_R.png");
    m_textures[0][1][1].loadFromFile("Resources/images/charakter_R1.png");
    m_textures[0][1][2].loadFromFile("Resources/images/charakter_R2.png");

    m_textures[1][0][0].loadFromFile("Resources/images/charakter_HL.png");
    m_textures[1][0][1].loadFromFile("Resources/images/charakter_HL1.png");
    m_textures[1][0][2].loadFromFile("Resources/images/charakter_HL2.png");

    m_textures[1][1][0].loadFromFile("Resources/images/charakter_HR.png");
    m_textures[1][1][1].loadFromFile("Resources/images/charakter_HR1.png");
    m_textures[1][1][2].loadFromFile("Resources/images/charakter_HR2.png");
    m_sprite.setTexture(m_textures[0][0][0]);

}

static int i = 0;
static int prevleft_right = 0;
static int prevfront_back = 0;
void Player::update(float deltatime)
{
    float speed_scalar = 1.0f;
    int left_right = -1;
    int front_back = -1;
    glm::vec3 dir(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        speed_scalar = 1.5f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        //if (Utils::Pathfinding::get_instance()->is_valid((m_pos + (glm::vec3{ 0.0f,-1.0f,0.0f } * 300.0f * deltatime * speed_scalar)) / 135.0f))
        //{
            //if (Utils::Pathfinding::get_instance()->get_map()[0][(m_pos.y - 1 * 300.0f * deltatime * speed_scalar) / 135][m_pos.x / 135] != Utils::Cell::WALL)
            //{
                //dir += glm::vec3(0, -1, 0);
            //}
        //}
       //else
        //{
        dir += glm::vec3(0, -1, 0);
        //}

        front_back = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {

        //if (Utils::Pathfinding::get_instance()->is_valid((m_pos + (glm::vec3{ 0.0f,1.0f,0.0f } * 300.0f * deltatime * speed_scalar)) / 135.0f))
        //{
         //   if (Utils::Pathfinding::get_instance()->get_map()[0][(m_pos.y + 1 * 300.0f * deltatime * speed_scalar) / 135][m_pos.x / 135] != Utils::Cell::WALL)
          //  {
           //     dir += glm::vec3(0, 1, 0);
                // }
        //}
        //else
        //{
        dir += glm::vec3(0, 1, 0);
        // }

        front_back = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {

        // if (Utils::Pathfinding::get_instance()->is_valid((m_pos + (glm::vec3{ -1.0f,0.0f,0.0f } * 300.0f * deltatime * speed_scalar)) / 135.0f))
        // {
        //     if (Utils::Pathfinding::get_instance()->get_map()[0][m_pos.y / 135][(m_pos.x - 1 * 300.0f * deltatime * speed_scalar) / 135] != Utils::Cell::WALL)
        //     {
         //    	dir += glm::vec3(-1, 0, 0);
       //      }
       //          
       //  }
       //  else
       //  {
        dir += glm::vec3(-1, 0, 0);
        //  }

        left_right = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        //if (Utils::Pathfinding::get_instance()->is_valid((m_pos + (glm::vec3{ 1.0f,0.0f,0.0f } * 300.0f * deltatime * speed_scalar)) / 135.0f))
        //{
        //    if (Utils::Pathfinding::get_instance()->get_map()[0][m_pos.y / 135][(m_pos.x + 1 * 300.0f * deltatime * speed_scalar) / 135] != Utils::Cell::WALL)
        //    {
        //        dir += glm::vec3(1, 0, 0);
        //    }
        //
        //}
        //else
        //{
        dir += glm::vec3(1, 0, 0);
        //}

        left_right = 1;
    }


    if (dir != glm::vec3{ 0,0,0 }) //um undefiniertes verhalten zu verhindern und zur optimierung
    {
        dir = glm::normalize(dir);
        /*LOG_TRACE("after normalize x:{:03.2f} y:{:03.2f} z:{:03.2f}", dir.x, dir.y, dir.z);*/
        dir *= 300 * speed_scalar * deltatime;
        m_pos += dir;
        speed = dir; // ich hol hier speed daten
        /* LOG_TRACE("after multiplying with 5 x:{:03.2f} y:{:03.2f} z:{:03.2f}", dir.x, dir.y, dir.z);*/

        cell_pos = round(glm::vec3{ m_pos.x / 135.0f,m_pos.y / 135.0f,m_pos.z });
        if (prev_pos != cell_pos)
        {
            prev_pos = cell_pos;
            EnemyManager::set_player_moving(true);
        }
        else
            EnemyManager::set_player_moving(false);



        /*LOG_TRACE("before normalize x:{:03.2f} y:{:03.2f} z:{:03.2f}", dir.x, dir.y, dir.z);*/


        i++;
        if (i == 1000)
            i = 0;
        if (front_back != -1)
            prevfront_back = front_back;
        if (left_right != -1)
            prevleft_right = left_right;

        if (i % 20 < 10)
        {
            m_sprite.setTexture(m_textures[prevfront_back][prevleft_right][1]);
        }
        else
        {
            m_sprite.setTexture(m_textures[prevfront_back][prevleft_right][2]);
        }
    }
    else
    {
        EnemyManager::set_player_moving(false);
        m_sprite.setTexture(m_textures[prevfront_back][prevleft_right][0]);
    }
    m_sprite.setPosition(m_pos.x, m_pos.y);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    //if (ImGui::ImageButton("test", m_sprite, { 50.0f,135.0f }))
    //{
    //    LOG_CRITICAL("button works");
    //}
    //ImGui::End();
    
    target.draw(m_sprite, states);
    
}

glm::ivec3 Player::getMovementSpeed() const {
    return speed;
}