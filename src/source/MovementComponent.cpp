#include "MovementComponent.hpp"

using namespace Components;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration)
	: m_sprite { sprite },
	m_max_speed{ max_speed }, m_moving_state{ MovingStates::IDLE }, m_dir_xy{ sf::Vector2f(0.f, 0.f)}, m_speed_dir{ sf::Vector2f(0.f, 0.f) },
	m_acceleration{ acceleration }, m_deceleration{ deceleration },
	m_first_speed_stage {m_max_speed / 3.f }, m_second_speed_stage{ m_max_speed / 2.f }, m_third_speed_stage{ m_max_speed / 1.1f }
{
}

MovementComponent::~MovementComponent()
{
}

////////////////////////////////////////////////////////////
// Accessors
////////////////////////////////////////////////////////////
const float Components::MovementComponent::getMaxSpeed() const
{
	return m_max_speed;
}

const sf::Vector2f MovementComponent::getSpeed() const
{
	return m_speed;
}

const sf::Vector2f Components::MovementComponent::getSpeedDir() const
{
	return m_speed_dir;
}

const float Components::MovementComponent::getSpeedStageX() const
{
	if (abs(m_speed.x) >= m_third_speed_stage)
		return 0.18f;
	if (abs(m_speed.x) >= m_second_speed_stage)
		return 0.15f;
	if (abs(m_speed.x) >= m_first_speed_stage)
		return 0.1f; 

	return 0.0f;
}

const MovementComponent::MovingStates MovementComponent::getMovingState() const
{
	return m_moving_state;
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
std::string MovementComponent::getStringInfo()
{
	std::stringstream result;

	result << "dir: x = " << m_dir_xy.x << " y = " << m_dir_xy.y << '\n';
	result << "speed_dir: x = " << m_speed_dir.x << " y = " << m_speed_dir.y << '\n';
	result << "speed: x = " << m_speed.x << " y = " << m_speed.y << '\n';
	result << "speed_stage: x = " << getSpeedStageX() << " y = " << "0" << '\n';

	switch (m_moving_state)
	{
	case MovingStates::NONE:
		result << "MovingState: NONE" << '\n';
		break;
	case MovingStates::IDLE:
		result << "MovingState: IDLE" << '\n';
		break;
	case MovingStates::RIGHT:
		result << "MovingState: RIGHT" << '\n';
		break;
	case MovingStates::LEFT:
		result << "MovingState: LEFT" << '\n';
		break;
	case Components::MovementComponent::MovingStates::DOWN:
		result << "MovingState: DOWN" << '\n';
		break;
	case Components::MovementComponent::MovingStates::UP:
		result << "MovingState: UP" << '\n';
		break;
	case Components::MovementComponent::MovingStates::BREAKING:
		result << "MovingState: BREAKING" << '\n';
		break;
	}

	return result.str();
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void MovementComponent::move(const sf::Vector2f& dir_xy, const float& dt)
{
	m_dir_xy = dir_xy;
	m_speed += m_acceleration * dir_xy;
}

inline void MovementComponent::updateState()
{
	if (m_speed_dir.x == 0.f && m_speed_dir.y == 0.f)
		m_moving_state = MovingStates::IDLE;
	else if ((m_dir_xy.x != 0 && m_dir_xy.x != m_speed_dir.x) || (m_dir_xy.y != 0 && m_dir_xy.y != m_speed_dir.y))
		m_moving_state = MovingStates::BREAKING;
	else if (m_speed_dir.x > 0.f)
		m_moving_state = MovingStates::RIGHT;
	else if (m_speed_dir.x < 0.f)
		m_moving_state = MovingStates::LEFT;
	else if (m_speed_dir.y > 0.f)
		m_moving_state = MovingStates::DOWN;
	else if (m_speed_dir.y < 0.f)
		m_moving_state = MovingStates::UP;
	else
		m_moving_state = MovingStates::NONE;
}

void MovementComponent::updateSpeedDir()
{
	if (m_speed.x > 0.f)
		m_speed_dir.x = 1.f;
	else if (m_speed.x < 0.f)
		m_speed_dir.x = -1.f;
	else
		m_speed_dir.x = 0.f;

	if (m_speed.y > 0.f)
		m_speed_dir.y = 1.f;
	else if (m_speed.y < 0.f)
		m_speed_dir.y = -1.f;
	else 
		m_speed_dir.y = 0.f;
}

void MovementComponent::update(const float& dt)
{
	maxSpeedCheck();
	updateState();
	updateSpeedDir();
	deceleration();

	m_sprite.move(m_speed * dt);
}

////////////////////////////////////////////////////////////
// Support functions
////////////////////////////////////////////////////////////
inline void MovementComponent::maxSpeedCheck()
{
	// x
	if (m_speed.x > 0.f)
	{
		if (m_speed.x > m_max_speed)
			m_speed.x = m_max_speed;
	}
	else if (m_speed.x < 0.f)
	{
		if (abs(m_speed.x) > m_max_speed)
			m_speed.x = -m_max_speed;
	}

	// y
	if (m_speed.y > 0.f)
	{
		if (m_speed.y > m_max_speed)
			m_speed.y = m_max_speed;
	}
	else if (m_speed.y < 0.f)
	{
		if (abs(m_speed.y) > m_max_speed)
			m_speed.y = -m_max_speed;
	}
}

/*
inline void MovementComponent::acceleration(const sf::Vector2f& dir_xy)
{
	m_speed += m_acceleration * dir_xy;
}
*/
inline void MovementComponent::deceleration()
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