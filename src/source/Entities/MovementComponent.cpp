#include "stdafx.h"

#include "MovementComponent.hpp"

using namespace Components;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& maxSpeed, const float& acceleration, const float& deceleration)
	: m_sprite          { sprite }
	, m_maxSpeed        { maxSpeed }
	, m_speedStage      { SpeedStage::NONE }
	, m_movingState     { MovingState::IDLE }
	, m_dir_xy          { sf::Vector2f(0.f, 0.f)}
	, m_speedDir        { sf::Vector2f(0.f, 0.f) }
	, m_acceleration    { acceleration }
	, m_deceleration    { deceleration }
	, m_firstSpeedStage { m_maxSpeed / 3.f }
	, m_secondSpeedStage{ m_maxSpeed / 1.7f }
	, m_thirdSpeedStage { m_maxSpeed / 1.1f }
{
}

MovementComponent::~MovementComponent()
{
}

// Accessors
const float Components::MovementComponent::GetMaxSpeed() const
{
	return m_maxSpeed;
}

const sf::Vector2f MovementComponent::GetSpeed() const
{
	return m_speed;
}

const sf::Vector2f Components::MovementComponent::GetSpeedDir() const
{
	return m_speedDir;
}

const MovementComponent::SpeedStage MovementComponent::GetSpeedStage() const
{
	return m_speedStage;
}

const MovementComponent::MovingState MovementComponent::GetMovingState() const
{
	return m_movingState;
}

// Info
std::string MovementComponent::GetStringInfo()
{
	std::stringstream result;

	result << "dir: x = " << m_dir_xy.x << " y = " << m_dir_xy.y << '\n';
	result << "speed_dir: x = " << m_speedDir.x << " y = " << m_speedDir.y << '\n';
	result << "speed: x = " << m_speed.x << " y = " << m_speed.y << '\n';

	switch (m_speedStage)
	{
	case SpeedStage::NONE:
		result << "SpeedStage: NONE" << '\n';
		break;
	case SpeedStage::FIRST:
		result << "SpeedStage: FIRST" << '\n';
		break;
	case SpeedStage::SECOND:
		result << "SpeedStage: SECOND" << '\n';
		break;
	case SpeedStage::THIRD:
		result << "SpeedStage: THIRD" << '\n';
		break;
	}

	switch (m_movingState)
	{
	case MovingState::NONE:
		result << "MovingState: NONE" << '\n';
		break;
	case MovingState::IDLE:
		result << "MovingState: IDLE" << '\n';
		break;
	case MovingState::RIGHT:
		result << "MovingState: RIGHT" << '\n';
		break;
	case MovingState::LEFT:
		result << "MovingState: LEFT" << '\n';
		break;
	case MovingState::DOWN:
		result << "MovingState: DOWN" << '\n';
		break;
	case MovingState::UP:
		result << "MovingState: UP" << '\n';
		break;
	case MovingState::BREAKING_RIGHT:
		result << "MovingState: BREAKING_RIGHT" << '\n';
		break;
	case MovingState::BREAKING_LEFT:
		result << "MovingState: BREAKING_LEFT" << '\n';
		break;
	}

	return result.str();
}

// Functions
void MovementComponent::Move(const sf::Vector2f& dir_xy, const float& dt)
{
	m_dir_xy = dir_xy;
	m_speed += m_acceleration * dir_xy;
}

void MovementComponent::UpdateSpeedDir()
{
	if (m_speed.x > 0.f)
		m_speedDir.x = 1.f;
	else if (m_speed.x < 0.f)
		m_speedDir.x = -1.f;
	else
		m_speedDir.x = 0.f;

	if (m_speed.y > 0.f)
		m_speedDir.y = 1.f;
	else if (m_speed.y < 0.f)
		m_speedDir.y = -1.f;
	else 
		m_speedDir.y = 0.f;
}

inline void Components::MovementComponent::UpdateSpeedStage()
{
	if (abs(m_speed.x) >= m_thirdSpeedStage)
		m_speedStage = SpeedStage::THIRD;
	else if (abs(m_speed.x) >= m_secondSpeedStage)
		m_speedStage = SpeedStage::SECOND;
	else if (abs(m_speed.x) >= m_firstSpeedStage)
		m_speedStage = SpeedStage::FIRST;
	else
		m_speedStage = SpeedStage::NONE;
}

inline void MovementComponent::UpdateState()
{
	bool is_breakingRight = (m_dir_xy.x == -1.f && m_speedDir.x == 1.f);
	bool is_breakingLeft  = (m_dir_xy.x == 1.f && m_speedDir.x == -1.f);
	//bool is_opposite_dir = (m_dir_xy.x != 0 && m_dir_xy.x != m_speed_dir.x) || (m_dir_xy.y != 0 && m_dir_xy.y != m_speed_dir.y);

	if (m_speedDir.x == 0.f && m_speedDir.y == 0.f)
		m_movingState = MovingState::IDLE;
	else if (is_breakingRight && m_speedStage > SpeedStage::FIRST)
		m_movingState = MovingState::BREAKING_RIGHT;
	else if (is_breakingLeft && m_speedStage > SpeedStage::FIRST)
		m_movingState = MovingState::BREAKING_LEFT;
	else if (m_speedDir.x > 0.f)
		m_movingState = MovingState::RIGHT;
	else if (m_speedDir.x < 0.f)
		m_movingState = MovingState::LEFT;
	else if (m_speedDir.y > 0.f)
		m_movingState = MovingState::DOWN;
	else if (m_speedDir.y < 0.f)
		m_movingState = MovingState::UP;
	else
		m_movingState = MovingState::NONE;
}

void MovementComponent::Update(const float& dt)
{
	MaxSpeedCheck();
	UpdateSpeedDir();
	UpdateSpeedStage();
	UpdateState();

	Deceleration();

	m_sprite.move(m_speed * dt);
}

// Support functions
inline void MovementComponent::MaxSpeedCheck()
{
	// x
	if (m_speed.x > 0.f)
	{
		if (m_speed.x > m_maxSpeed)
			m_speed.x = m_maxSpeed;
	}
	else if (m_speed.x < 0.f)
	{
		if (abs(m_speed.x) > m_maxSpeed)
			m_speed.x = -m_maxSpeed;
	}

	// y
	if (m_speed.y > 0.f)
	{
		if (m_speed.y > m_maxSpeed)
			m_speed.y = m_maxSpeed;
	}
	else if (m_speed.y < 0.f)
	{
		if (abs(m_speed.y) > m_maxSpeed)
			m_speed.y = -m_maxSpeed;
	}
}

/*
inline void MovementComponent::acceleration(const sf::Vector2f& dir_xy)
{
	m_speed += m_acceleration * dir_xy;
}
*/
inline void MovementComponent::Deceleration()
{
	// x
	if (m_speed.x > 0.f) //Positive position
	{
		m_speed.x -= m_deceleration;
		if (m_speed.x < 0.f)
			m_speed.x = 0.f;
	}
	else if (m_speed.x < 0.f) //Negative position
	{
		m_speed.x += m_deceleration;
		if (abs(m_speed.x) < 0.f)
			m_speed.x = 0.f;
	}

	// y
	if (m_speed.y > 0.f) //Positive position
	{
		m_speed.y -= m_deceleration;
		if (m_speed.y < 0.f)
			m_speed.y = 0.f;
	}
	else if (m_speed.y < 0.f) //Negative position
	{
		m_speed.y += m_deceleration;
		if (abs(m_speed.y) < 0.f)
			m_speed.y = 0.f;
	}
}