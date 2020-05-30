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
// Init
////////////////////////////////////////////////////////////
void Player::initAnimations()
{
	//addAnimation(NAME, TIME_OF_ANIM (sec), START_X, START_Y, FRAMES_X, FRAMES_Y, WIDTH, HEIGHT)
	m_animation_component->addAnimation("WALK_RIGHT", 0.35f, 1, 1, 5, 1, 50, 37);

	m_animation_component->addAnimation("IDLE", 0.35f, 0, 0, 3, 0, 50, 37); //Need last, because it's a start Rect
}

////////////////////////////////////////////////////////////
// Accessors
////////////////////////////////////////////////////////////
float Player::getValueSpeedStageX() const
{
	return m_movement_component->getSpeedStageX();
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
	using MoveState = Components::MovementComponent::States;

	MoveState movement_state = m_movement_component->getState();

	switch (movement_state)
	{
	case MoveState::IDLE:
		m_animation_component->play("IDLE", dt);
		break;
	case MoveState::MOVING_RIGHT:
		m_animation_component->play("WALK_RIGHT", dt, m_movement_component->getSpeedStageX());
		break;
	case MoveState::MOVING_LEFT:
		break;
	case MoveState::MOVING_UP:
		break;
	case MoveState::MOVING_DOWN:
		break;
	}		
}

void Player::updateInput()
{
}