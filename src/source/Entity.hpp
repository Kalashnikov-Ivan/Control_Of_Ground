#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.hpp"

namespace cog
{
class Entity
{
public:
	//Constructors
	Entity(sf::Texture* texture, const float& max_speed);
	virtual ~Entity();

	//Functions
	virtual void move(const float& dt, const sf::Vector2f& dir_xy);

	//Modifiers
	virtual void set_position(const sf::Vector2f& position_xy);

	//Virtual
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

protected:
	//Members
	sf::Sprite* m_sprite;

	//Components
	MovementComponent* m_movement_component;

	//Init
	void set_texture(sf::Texture* texture);

private:

};
} // !namespace cog
#endif // !ENTITY_H