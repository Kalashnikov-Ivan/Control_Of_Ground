#include "MovementComponent.hpp"

using namespace Components;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration)
	: m_sprite { sprite },
	m_max_speed{ max_speed }, m_state{ States::IDLE },
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

const sf::Vector2f Components::MovementComponent::getDirMove() const
{
	return m_dir_xy;
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

const MovementComponent::States MovementComponent::getState() const
{
	return m_state;
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
std::string MovementComponent::getStringInfo()
{
	std::stringstream result;

	result << "dir: x = " << m_dir_xy.x << " y = " << m_dir_xy.y << '\n';
	result << "speed: x = " << m_speed.x << " y = " << m_speed.y << '\n';
	result << "speed_stage: x = " << getSpeedStageX() << " y = " << "0" << '\n';

	switch (m_state)
	{
	case Components::MovementComponent::States::NONE:
		result << "state: NONE" << '\n';
		break;
	case Components::MovementComponent::States::IDLE:
		result << "state: IDLE" << '\n';
		break;
	case Components::MovementComponent::States::MOVING_RIGHT:
		result << "state: MOVING_RIGHT" << '\n';
		break;
	case Components::MovementComponent::States::MOVING_LEFT:
		result << "state: MOVING_LEFT" << '\n';
		break;
	case Components::MovementComponent::States::MOVING_DOWN:
		result << "state: MOVING_DOWN" << '\n';
		break;
	case Components::MovementComponent::States::MOVING_UP:
		result << "state: MOVING_UP" << '\n';
		break;
	case Components::MovementComponent::States::BREAKING:
		result << "state: BREAKING" << '\n';
		break;
	}

	return result.str();
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void MovementComponent::move(const sf::Vector2f& dir_xy, const float& dt)
{
	if (m_dir_xy.x == -1 && m_speed.x > 0)
	{
		m_state = States::BREAKING;
	}

	m_dir_xy = dir_xy;
	m_speed += m_acceleration * m_dir_xy;
}

void MovementComponent::update(const float& dt)
{
	maxSpeedCheck();
	updateState();
	deceleration();

	m_sprite.move(m_speed * dt);
}

inline void MovementComponent::updateState()
{
	if (m_speed.x == 0.f && m_speed.y == 0.f)
		m_state = States::IDLE;
	else if (m_speed.x > 0.f)
		m_state = States::MOVING_RIGHT;
	else if (m_speed.x < 0.f)
		m_state = States::MOVING_LEFT;
	else if (m_speed.y > 0.f)
		m_state = States::MOVING_DOWN;
	else if (m_speed.y < 0.f)
		m_state = States::MOVING_UP;
	else
		m_state = States::NONE;
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