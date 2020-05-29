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
	//init_animations();

	setPosition(position_xy);
	m_sprite->setScale(sf::Vector2f(0.12f, 0.15f));
}

Player::~Player()
{
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void Player::update(const float& dt)
{
	Entity::update(dt);

	//update_animations(dt);
}

void Player::updateAnimations(const float& dt)
{
	m_animation_component->play("IDLE", dt);
}

void Player::updateInput()
{
}


////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void Player::initAnimations()
{
	m_animation_component->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
}