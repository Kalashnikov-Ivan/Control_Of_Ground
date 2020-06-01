#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.hpp"
#include "AnimationComponent.hpp"
#include "HitboxComponent.hpp"

namespace Entities
{
class Entity
{
public:
	//Constructors
	Entity(sf::Texture& texture, const sf::Vector2f& scale = sf::Vector2f(1.f, 1.f));
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
	virtual void render(sf::RenderTarget& target);

protected:
	//Members
	sf::Sprite* m_sprite;

	//Components
	Components::MovementComponent*  m_movement_component;
	Components::AnimationComponent* m_animation_component;
	Components::HitboxComponent* m_hitbox_component;

	//Creators
	void createMovementComponent (sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration);
	void createAnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	void createHitboxComponent   (sf::Sprite& sprite, const sf::Vector2f& offset_xy, const sf::Vector2f& size_xy, const sf::Vector2f& scale = sf::Vector2f(1.f, 1.f));

private:

};
} // !namespace cog
#endif // !ENTITY_H