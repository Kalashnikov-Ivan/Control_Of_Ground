#include "stdHeader.hpp"

#include "Player.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Player::Player(const sf::Vector2f& position_xy, sf::Texture& texture, 
			   const float& max_speed, const float& acceleration, const float& deceleration)
	: Entity(texture, max_speed, acceleration, deceleration)
{
	set_position(position_xy);
	m_sprite->setScale(sf::Vector2f(0.12f, 0.15f));
}

Player::~Player()
{
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void update_input()
{

}