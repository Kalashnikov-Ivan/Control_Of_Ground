#include "MovementComponent.hpp"

using namespace Components;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MovementComponent::MovementComponent(sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration)
	: m_sprite { sprite },
	m_max_speed{ max_speed }, m_speed_stage{ SpeedStages::NONE }, m_moving_state{ MovingStates::IDLE },
	m_dir_xy{ sf::Vector2f(0.f, 0.f)}, m_speed_dir{ sf::Vector2f(0.f, 0.f) },
	m_acceleration{ acceleration }, m_deceleration{ deceleration },
	m_first_speed_stage {m_max_speed / 3.f }, m_second_speed_stage{ m_max_speed / 1.7f }, m_third_speed_stage{ m_max_speed / 1.1f }
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

const MovementComponent::SpeedStages MovementComponent::getSpeedStage() const
{
	return m_speed_stage;
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

	switch (m_speed_stage)
	{
	case SpeedStages::NONE:
		result << "SpeedStage: NONE" << '\n';
		break;
	case SpeedStages::FIRST:
		result << "SpeedStage: FIRST" << '\n';
		break;
	case SpeedStages::SECOND:
		result << "SpeedStage: SECOND" << '\n';
		break;
	case SpeedStages::THIRD:
		result << "SpeedStage: THIRD" << '\n';
		break;
	}

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
	case MovingStates::DOWN:
		result << "MovingState: DOWN" << '\n';
		break;
	case MovingStates::UP:
		result << "MovingState: UP" << '\n';
		break;
	case MovingStates::BREAKING_RIGHT:
		result << "MovingState: BREAKING_RIGHT" << '\n';
		break;
	case MovingStates::BREAKING_LEFT:
		result << "MovingState: BREAKING_LEFT" << '\n';
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

inline void Components::MovementComponent::updateSpeedStage()
{
	if (abs(m_speed.x) >= m_third_speed_stage)
		m_speed_stage = SpeedStages::THIRD;
	else if (abs(m_speed.x) >= m_second_speed_stage)
		m_speed_stage = SpeedStages::SECOND;
	else if (abs(m_speed.x) >= m_first_speed_stage)
		m_speed_stage = SpeedStages::FIRST;
	else
		m_speed_stage = SpeedStages::NONE;
}

inline void MovementComponent::updateState()
{
	bool is_breaking_right = (m_dir_xy.x == -1.f && m_speed_dir.x == 1.f);
	bool is_breaking_left = (m_dir_xy.x == 1.f && m_speed_dir.x == -1.f);
	//bool is_opposite_dir = (m_dir_xy.x != 0 && m_dir_xy.x != m_speed_dir.x) || (m_dir_xy.y != 0 && m_dir_xy.y != m_speed_dir.y);

	if (m_speed_dir.x == 0.f && m_speed_dir.y == 0.f)
		m_moving_state = MovingStates::IDLE;
	else if (is_breaking_right && m_speed_stage > SpeedStages::FIRST)
		m_moving_state = MovingStates::BREAKING_RIGHT;
	else if (is_breaking_left && m_speed_stage > SpeedStages::FIRST)
		m_moving_state = MovingStates::BREAKING_LEFT;
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

void MovementComponent::update(const float& dt)
{
	maxSpeedCheck();
	updateSpeedDir();
	updateSpeedStage();
	updateState();

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