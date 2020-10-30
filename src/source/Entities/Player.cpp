#include "stdafx.h"

#include "Player.hpp"

using namespace Entities;

// Constructors
Player::Player(const sf::Vector2f& position_xy, sf::Texture& texture,
			   const float& maxSpeed, const float& acceleration, const float& deceleration,
			   const sf::Vector2f& scale)
	: Entity     { texture, scale }
	, m_scale_x  { scale.x }
	, m_scale_y  { scale.y }
	, m_attacking{ false }
{
	//Creating components
	createMovementComponent (m_sprite, maxSpeed, acceleration, deceleration);
	createAnimationComponent(m_sprite, texture);

	sf::Vector2f hitboxSize{ 11.f, 26.f };
	createHitboxComponent   (m_sprite, sf::Vector2f(80.f, 25.f), hitboxSize, scale);

	InitAnimations();

	SetPosition(position_xy);
}

Player::~Player()
{
}

// Init
void Player::InitAnimations()
{
	//addAnimation                    (NAME, TIME_OF_ANIM (sec), START_X, START_Y, FRAMES_X, FRAMES_Y, WIDTH, HEIGHT)
	m_animationСomponent->AddAnimation("ATTACK_1",  10.f, 0, 3, 5, 3, 50, 37);
	m_animationСomponent->AddAnimation("BREAKING", 15.f, 0, 2, 4, 2, 50, 37);
	m_animationСomponent->AddAnimation("WALK",     10.f, 0, 1, 5, 1, 50, 37);
	m_animationСomponent->AddAnimation("IDLE",     25.f, 0, 0, 3, 0, 50, 37); //Need last, because it's a start Rect
}

// Info
std::string Player::GetStringInfo()
{
	std::stringstream result;

	result << "Player_pos: " << m_sprite.getPosition().x << ' ' << m_sprite.getPosition().y << '\n';
	result << "MovementComponent:\n";
	result << m_movementСomponent->GetStringInfo();

	result << std::boolalpha;
	result << "ATTACKING: " << m_attacking << '\n';

	return result.str();
}

// Functions
void Player::Move(const sf::Vector2f& dir_xy, const float& dt)
{
	m_movementСomponent->Move(dir_xy, dt);
}

// Update
void Player::UpdateAnimations(const float& dt)
{
	using MoveState = Components::MovementComponent::MovingState;

	MoveState movementState = m_movementСomponent->GetMovingState();

	float modifierSpeedAnim = m_movementСomponent->GetSpeed().x;
	float modifierMax       = m_movementСomponent->GetMaxSpeed();

	if (m_attacking)
	{
		if (m_animationСomponent->Play("ATTACK_1", dt, 1.f, 1.f, true))
			m_attacking = false;
	}

	switch (movementState)
	{
	case MoveState::IDLE:
		m_hitboxComponent->SetPosition(sf::Vector2f(0.f, 0.f));
		m_hitboxComponent->SetSize(sf::Vector2f(11.f, 29.f));
		m_hitboxComponent->SetOffsetMove(sf::Vector2f(0.f, 0.f));
		m_hitboxComponent->SetRotation(0.f);
		m_animationСomponent->Play("IDLE", dt, 1.f, 1.f);
		break;
	case MoveState::RIGHT:
		m_sprite.setOrigin(0.f, 0.f);
		m_sprite.setScale(m_scale_x, m_scale_y);
		m_hitboxComponent->SetPosition(sf::Vector2f(0.f, 0.f));
		m_hitboxComponent->SetSize(sf::Vector2f(11.f, 29.f));
		m_hitboxComponent->SetOffsetMove(sf::Vector2f(7.f, 0.f));
		m_hitboxComponent->SetRotation(7.f);
		m_animationСomponent->Play("WALK", dt, modifierSpeedAnim, modifierMax);
		break;
	case MoveState::LEFT:
		m_sprite.setOrigin(50.f, 0.f);
		m_sprite.setScale(-m_scale_x, m_scale_y);
		m_hitboxComponent->SetPosition(sf::Vector2f(0.f, 0.f));
		m_hitboxComponent->SetSize(sf::Vector2f(11.f, 29.f));
		m_hitboxComponent->SetOffsetMove(sf::Vector2f(-7.f, 0.f));
		m_hitboxComponent->SetRotation(-7.f);
		m_animationСomponent->Play("WALK", dt, modifierSpeedAnim, modifierMax);
		break;
	case MoveState::UP:
		m_animationСomponent->Play("WALK", dt, modifierSpeedAnim, modifierMax);
		break;
	case MoveState::DOWN:
		m_animationСomponent->Play("WALK", dt, modifierSpeedAnim, modifierMax);
		break;
	case MoveState::BREAKING_RIGHT:
		m_hitboxComponent->SetSize(sf::Vector2f(25.f, 13.f));
		m_hitboxComponent->SetOffsetMove(sf::Vector2f(-13.f, 53.f));
		m_hitboxComponent->SetRotation(0.f);
		m_animationСomponent->Play("BREAKING", dt, modifierSpeedAnim, modifierMax);
		break;
	case MoveState::BREAKING_LEFT:
		m_hitboxComponent->SetSize(sf::Vector2f(25.f, 13.f));
		m_hitboxComponent->SetOffsetMove(sf::Vector2f(-44.f, 53.f));
		m_hitboxComponent->SetRotation(0.f);
		m_animationСomponent->Play("BREAKING", dt, modifierSpeedAnim, modifierMax);
		break;
	}		
}

void Player::UpdateInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_attacking = true;
}

void Player::Update(const float& dt)
{
	UpdateInput();

	m_movementСomponent->Update(dt);

	UpdateAnimations(dt);

	m_hitboxComponent->Update(dt);
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(m_sprite);
	m_hitboxComponent->Render(target);
}