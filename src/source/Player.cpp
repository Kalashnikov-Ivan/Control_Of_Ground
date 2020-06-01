#include "stdHeader.hpp"

#include "Player.hpp"

using namespace Entities;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Player::Player(const sf::Vector2f& position_xy, sf::Texture& texture,
			   const float& max_speed, const float& acceleration, const float& deceleration,
			   const sf::Vector2f& scale)
	: Entity{ texture, scale }, m_scale_x { scale.x }, m_scale_y{ scale.y }
{
	//Creating components
	createMovementComponent (*m_sprite, max_speed, acceleration, deceleration);
	createAnimationComponent(*m_sprite, texture);
	sf::Vector2f hitbox_size{ 11.f, 29.f };
	createHitboxComponent   (*m_sprite, sf::Vector2f(80.f, 30.f), hitbox_size, scale);

	initAnimations();

	setPosition(position_xy);
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
	m_animation_component->addAnimation("WALK", 0.35f, 1, 1, 5, 1, 50, 37);

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
	m_hitbox_component->update(dt);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(*m_sprite);
	m_hitbox_component->render(target);
}

void Player::updateAnimations(const float& dt)
{
	using MoveState = Components::MovementComponent::States;

	MoveState movement_state = m_movement_component->getState();

	switch (movement_state)
	{
	case MoveState::IDLE:
		m_hitbox_component->setOffsetMove(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setRotation(0.f);
		m_animation_component->play("IDLE", dt);
		break;
	case MoveState::MOVING_RIGHT:
		m_sprite->setOrigin(0.f, 0.f);
		m_sprite->setScale(m_scale_x, m_scale_y);
		m_hitbox_component->setOffsetMove(sf::Vector2f(23.f, 0.f));
		m_hitbox_component->setRotation(7.f);
		m_animation_component->play("WALK", dt, m_movement_component->getSpeedStageX());
		break;
	case MoveState::MOVING_LEFT:
		m_sprite->setOrigin(50.f, 0.f);
		m_sprite->setScale(-m_scale_x, m_scale_y);
		m_hitbox_component->setOffsetMove(sf::Vector2f(-23.f, 0.f));
		m_hitbox_component->setRotation(-7.f);
		m_animation_component->play("WALK", dt, m_movement_component->getSpeedStageX());
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