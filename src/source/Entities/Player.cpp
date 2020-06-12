#include "stdHeader.hpp"

#include "Player.hpp"

using namespace Entities;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Player::Player(const sf::Vector2f& position_xy, sf::Texture& texture,
			   const float& max_speed, const float& acceleration, const float& deceleration,
			   const sf::Vector2f& scale)
	: Entity{ texture, scale }, m_scale_x { scale.x }, m_scale_y{ scale.y },
	m_is_attacking{ false }
{
	//Creating components
	createMovementComponent (*m_sprite, max_speed, acceleration, deceleration);
	createAnimationComponent(*m_sprite, texture);
	sf::Vector2f hitbox_size{ 11.f, 26.f };
	createHitboxComponent   (*m_sprite, sf::Vector2f(80.f, 25.f), hitbox_size, scale);

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
	//addAnimation                      (NAME, TIME_OF_ANIM (sec), START_X, START_Y, FRAMES_X, FRAMES_Y, WIDTH, HEIGHT)
	m_animation_component->addAnimation("ATTACK_1",  10.f, 0, 3, 5, 3, 50, 37);
	m_animation_component->addAnimation("BREAKING", 15.f, 0, 2, 4, 2, 50, 37);
	m_animation_component->addAnimation("WALK",     10.f, 0, 1, 5, 1, 50, 37);
	m_animation_component->addAnimation("IDLE",     25.f, 0, 0, 3, 0, 50, 37); //Need last, because it's a start Rect
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
std::string Player::getStringInfo()
{
	std::stringstream result;

	result << "Player_pos: " << m_sprite->getPosition().x << ' ' << m_sprite->getPosition().y << '\n';
	result << "MovementComponent:\n";
	result << m_movement_component->getStringInfo();

	result << std::boolalpha;
	result << "ATTACKING: " << m_is_attacking << '\n';

	return result.str();
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

void Player::move(const sf::Vector2f& dir_xy, const float& dt)
{
	m_movement_component->move(dir_xy, dt);
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void Player::updateAnimations(const float& dt)
{
	using MoveState  = Components::MovementComponent::MovingStates;

	MoveState movement_state = m_movement_component->getMovingState();

	float modifier_speed_anim = m_movement_component->getSpeed().x;
	float modifier_max        = m_movement_component->getMaxSpeed();

	if (m_is_attacking)
	{
		if (m_animation_component->play("ATTACK_1", dt, 1.f, 1.f, true))
			m_is_attacking = false;
	}

	switch (movement_state)
	{
	case MoveState::IDLE:
		m_hitbox_component->setPosition(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setSize(sf::Vector2f(11.f, 29.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setRotation(0.f);
		m_animation_component->play("IDLE", dt, 1.f, 1.f);
		break;
	case MoveState::RIGHT:
		m_sprite->setOrigin(0.f, 0.f);
		m_sprite->setScale(m_scale_x, m_scale_y);
		m_hitbox_component->setPosition(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setSize(sf::Vector2f(11.f, 29.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(7.f, 0.f));
		m_hitbox_component->setRotation(7.f);
		m_animation_component->play("WALK", dt, modifier_speed_anim, modifier_max);
		break;
	case MoveState::LEFT:
		m_sprite->setOrigin(50.f, 0.f);
		m_sprite->setScale(-m_scale_x, m_scale_y);
		m_hitbox_component->setPosition(sf::Vector2f(0.f, 0.f));
		m_hitbox_component->setSize(sf::Vector2f(11.f, 29.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(-7.f, 0.f));
		m_hitbox_component->setRotation(-7.f);
		m_animation_component->play("WALK", dt, modifier_speed_anim, modifier_max);
		break;
	case MoveState::UP:
		m_animation_component->play("WALK", dt, modifier_speed_anim, modifier_max);
		break;
	case MoveState::DOWN:
		m_animation_component->play("WALK", dt, modifier_speed_anim, modifier_max);
		break;
	case MoveState::BREAKING_RIGHT:
		m_hitbox_component->setSize(sf::Vector2f(25.f, 13.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(-13.f, 53.f));
		m_hitbox_component->setRotation(0.f);
		m_animation_component->play("BREAKING", dt, modifier_speed_anim, modifier_max);
		break;
	case MoveState::BREAKING_LEFT:
		m_hitbox_component->setSize(sf::Vector2f(25.f, 13.f));
		m_hitbox_component->setOffsetMove(sf::Vector2f(-44.f, 53.f));
		m_hitbox_component->setRotation(0.f);
		m_animation_component->play("BREAKING", dt, modifier_speed_anim, modifier_max);
		break;
	}		
}

void Player::updateInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_is_attacking = true;
}

void Player::update(const float& dt)
{
	updateInput();

	m_movement_component->update(dt);

	updateAnimations(dt);

	m_hitbox_component->update(dt);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(*m_sprite);
	m_hitbox_component->render(target);
}