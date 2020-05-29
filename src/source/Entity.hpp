#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.hpp"
#include "AnimationComponent.hpp"

namespace cog
{
class Entity
{
public:
	//Constructors
	Entity(sf::Texture& texture, 
		   const float& max_speed, const float& acceleration, const float& deceleration);
	virtual ~Entity();

	//Accessors
	sf::Vector2f getSpeed() const;

	//Modifiers
	virtual void setPosition(const sf::Vector2f& position_xy);
	virtual void setTexture(const sf::Texture& texture);

	//Functions
	virtual void move(const sf::Vector2f& dir_xy, const float& dt);

	//Virtual
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

protected:
	//Members
	sf::Sprite* m_sprite;

	//Components
	MovementComponent*  m_movement_component;
	AnimationComponent* m_animation_component;

private:

};
} // !namespace cog
#endif // !ENTITY_H