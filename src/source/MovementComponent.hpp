#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "stdHeader.hpp"

namespace Components
{
class MovementComponent
{
public:
	enum class States { IDLE = 0, MOVING_RIGHT };

	//Constructors
	MovementComponent(sf::Sprite& sprite, const float& max_speed, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& getSpeed() const;
	const bool checkState(const States state) const;

	//Functions
	void move(const sf::Vector2f& dir_xy, const float& dt);
	void update(const float& dt);
private:
	//Members
	sf::Sprite& m_sprite;

	float m_max_speed;
	float m_acceleration;
	float m_deceleration;

	sf::Vector2f m_speed;

	//Support functions
	inline void acceleration(const sf::Vector2f& dir_xy);
	inline void deceleration();

	inline void maxSpeedCheck();
};
} // !namespace cog

#endif // !MOVEMENT_COMPONENT_H