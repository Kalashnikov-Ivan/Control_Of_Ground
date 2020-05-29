#include "MovementComponent.hpp"

using namespace Components;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& max_speed, float acceleration, float deceleration)
	: m_sprite { sprite },
	m_max_speed{ max_speed },
	m_acceleration{ acceleration }, m_deceleration{ deceleration }
{
}

MovementComponent::~MovementComponent()
{
}

////////////////////////////////////////////////////////////
// Accessors
////////////////////////////////////////////////////////////
const sf::Vector2f& MovementComponent::getSpeed() const
{
	return m_speed;
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
	}
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