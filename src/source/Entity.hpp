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
		const sf::Vector2f getSpeed() const;
		const sf::Vector2f getDirMove() const;
		const float getValueSpeedStageX() const;

	//Modifiers
		void setPosition(const sf::Vector2f& position_xy);
		void setTexture(const sf::Texture& texture);

	//Info
		virtual std::string getStringInfo() = 0;

	//Functions
		virtual void move(const sf::Vector2f& dir_xy, const float& dt) = 0;

	//Update and render
		virtual void update(const float& dt) = 0;
		virtual void render(sf::RenderTarget& target) = 0;

protected:
	//Members
	sf::Sprite* m_sprite;

	//Components
	Components::MovementComponent*  m_movement_component;
	Components::AnimationComponent* m_animation_component;
	Components::HitboxComponent*    m_hitbox_component;

	//Creators
	void createMovementComponent (sf::Sprite& sprite, const float& max_speed, const float& acceleration, const float& deceleration);
	void createAnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	void createHitboxComponent   (sf::Sprite& sprite, const sf::Vector2f& offset_xy, const sf::Vector2f& size_xy, const sf::Vector2f& scale = sf::Vector2f(1.f, 1.f));

private:

};
} // !namespace Entities
#endif // !ENTITY_H