#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "stdHeader.hpp"

namespace Components
{
class MovementComponent
{
public:
	enum class States { NONE = -1, IDLE = 0, MOVING_RIGHT, MOVING_LEFT, MOVING_DOWN, MOVING_UP, BREAKING };

	//Constructors
	MovementComponent(sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration);
	virtual ~MovementComponent();

	//Accessors
	//Speed
	const float getMaxSpeed() const;
	const sf::Vector2f getSpeed() const;
	const sf::Vector2f getDirMove() const;
	const float getSpeedStageX() const;
	//State
	const States getState() const;

	//Functions
	void move(const sf::Vector2f& dir_xy, const float& dt);
	void update(const float& dt);

	//Info
	std::string 
private:
	//Members
	sf::Sprite& m_sprite;

	//Speed
	float m_max_speed;
	float m_acceleration;
	float m_deceleration;

	sf::Vector2f m_dir_xy;
	sf::Vector2f m_speed;
	States m_state;

	float m_first_speed_stage;
	float m_second_speed_stage;
	float m_third_speed_stage;

	inline void updateState();

	//Support functions
	//inline void acceleration(const sf::Vector2f& dir_xy);
	inline void deceleration();

	inline void maxSpeedCheck();
};
} // !namespace cog

#endif // !MOVEMENT_COMPONENT_H