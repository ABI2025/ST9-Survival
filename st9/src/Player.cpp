#include "Player.h"

#include <iostream>

Player::Player()
	: Entity(2),rec({ 100.0f,100.0f })

{
	m_pos = {720, 720, 0};
	rec.setPosition(720, 720);
	rec.setSize({ 100.0f,100.0f });
	
}

void Player::update()
{
	rec.setPosition({ m_pos.x,m_pos.y });
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rec,states);
}
