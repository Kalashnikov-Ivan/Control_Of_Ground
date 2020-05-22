#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "stdHeader.hpp"

namespace cog
{
class MovementComponent
{
public:
	//Constructors
	MovementComponent(sf::Sprite& sprite, const float& max_speed);
	virtual ~MovementComponent();

	//Accessors
	const sf::Vector2f& get_speed() const;

	//Functions
	void move(sf::Vector2f dir_xy, const float& dt);
	void update(const float& dt);
private:
	//Members
	sf::Sprite& m_sprite;

	float m_max_speed;
	sf::Vector2f m_speed;
	sf::Vector2f m_acceleration;
};
} // !namespace cog

#endif // !MOVEMENT_COMPONENT_H