#include "stdHeader.hpp"

#include "Player.hpp"

using namespace Entities;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Player::Player(const sf::Vector2f& position_xy, sf::Texture& texture, 
			   const float& max_speed, const float& acceleration, const float& deceleration)
	: Entity(texture, max_speed, acceleration, deceleration)
{
	initAnimations();

	setPosition(position_xy);
	m_sprite->setScale(sf::Vector2f(4.f, 4.f));
}

Player::~Player()
{
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void Player::update(const float& dt)
{
	m_movement_component->update(dt);

	updateAnimations(dt);
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
	//addAnimation(NAME, TIME_OF_ANIM (sec), START_X, START_Y, FRAMES_X, FRAMES_Y, WIDTH, HEIGHT)
	m_animation_component->addAnimation("IDLE", 0.35f, 0, 0, 3, 0, 50, 37);
	m_animation_component->addAnimation("WALK_RIGHT", 0.35f, 1, 5, 0, 0, 50, 37);
}