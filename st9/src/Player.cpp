#include "Player.h"

#include <iostream>

Player::Player()
	: Entity()

{
	m_pos = {720, 720, 0};
    textures.resize(2);
    for(auto& t: textures)
    {
        t.resize(3);
			for(auto& tt :t)
			{
                tt.resize(3);
			}
    }

    textures[0][0][0].loadFromFile("Resources/charakter_L.png");
    textures[0][0][1].loadFromFile("Resources/charakter_L1.png");
    textures[0][0][2].loadFromFile("Resources/charakter_L2.png");
                                            
    textures[0][1][0].loadFromFile("Resources/charakter_R.png");
    textures[0][1][1].loadFromFile("Resources/charakter_R1.png");
    textures[0][1][2].loadFromFile("Resources/charakter_R2.png");
                                            
    textures[1][0][0].loadFromFile("Resources/charakter_HL.png");
    textures[1][0][1].loadFromFile("Resources/charakter_HL1.png");
    textures[1][0][2].loadFromFile("Resources/charakter_HL2.png");

	textures[1][1][0].loadFromFile("Resources/charakter_HR.png");
    textures[1][1][1].loadFromFile("Resources/charakter_HR1.png");
    textures[1][1][2].loadFromFile("Resources/charakter_HR2.png");
    m_sprite.setTexture(textures[0][0][0]);
	
}
static int i = 0;
static int prevleft_right = 0;
static int prevfront_back = 0;
void Player::update()
{
    int left_right = -1;
    int front_back = -1;
	glm::vec3 dir(0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        dir += glm::vec3(0, -1, 0);
        front_back = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        dir += glm::vec3(0, 1, 0);
        front_back = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        dir += glm::vec3(-1, 0, 0);
        left_right = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        dir += glm::vec3(1, 0, 0);
        left_right = 1;
    }
    if (dir != glm::vec3{ 0,0,0 }) //um undefiniertes verhalten zu verhindern und zur optimierung
    {

        /*LOG_TRACE("before normalize x:{:03.2f} y:{:03.2f} z:{:03.2f}", dir.x, dir.y, dir.z);*/
        dir = glm::normalize(dir);
        /*LOG_TRACE("after normalize x:{:03.2f} y:{:03.2f} z:{:03.2f}", dir.x, dir.y, dir.z);*/
        dir *= 5;
        m_pos += dir;
        /* LOG_TRACE("after multiplying with 5 x:{:03.2f} y:{:03.2f} z:{:03.2f}", dir.x, dir.y, dir.z);*/
        i++;
        if (i == 1000)
            i = 0;
        if(front_back != -1)
			prevfront_back = front_back;
        if (left_right != -1)
            prevleft_right = left_right;
        
        if(i % 20 < 10)
        {
            m_sprite.setTexture(textures[prevfront_back][prevleft_right][1]);
        }
        else
        {
            m_sprite.setTexture(textures[prevfront_back][prevleft_right][2]);
        }
    }
    else
    {
        m_sprite.setTexture(textures[prevfront_back][prevleft_right][0]);
    }
    m_sprite.setPosition(m_pos.x, m_pos.y);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite,states);
}
