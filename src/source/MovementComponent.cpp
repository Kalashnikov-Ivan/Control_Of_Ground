#include "MovementComponent.hpp"

using namespace Components;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration)
	: m_sprite { sprite },
	m_max_speed{ max_speed },
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

const sf::Vector2f& MovementComponent::getSpeed() const
{
	return m_speed;
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
	if (m_speed.x == 0.f && m_speed.y == 0.f)
		return States::IDLE;
	else if (m_speed.x > 0.f)
		return States::MOVING_RIGHT;
	else if (m_speed.x < 0.f)
		return States::MOVING_LEFT;
	else if (m_speed.y > 0.f)
		return States::MOVING_DOWN;
	else if (m_speed.y < 0.f)
		return States::MOVING_UP;

	return States::NONE;
}

const bool MovementComponent::checkState(const States state) const
{
	switch (state)
	{
	case States::IDLE:
		if (m_speed.x == 0.f && m_speed.y == 0.f)
			return true;
		break;
	case States::MOVING_RIGHT:
		if (m_speed.x > 0.f)
			return true;
		break;
	case States::MOVING_LEFT:
		if (m_speed.x < 0.f)
			return true;
		break;
	}

	return false;
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void MovementComponent::move(const sf::Vector2f& dir_xy, const float& dt)
{
	acceleration(dir_xy);
}

void MovementComponent::update(const float& dt)
{
	maxSpeedCheck();
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

inline void MovementComponent::acceleration(const sf::Vector2f& dir_xy)
{
	m_speed += m_acceleration * dir_xy;
}

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