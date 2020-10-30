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
	const sf::Vector2f GetSpeed() const;
	const sf::Vector2f GetSpeedDir() const;

//Modifiers
	void SetPosition(const sf::Vector2f& position_xy);
	void SetTexture(const sf::Texture& texture);

//Info
	virtual std::string GetStringInfo() = 0;

//Functions
	virtual void Move(const sf::Vector2f& dir_xy, const float& dt) = 0;

//Update and Render
	virtual void Update(const float& dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;

protected:
//Members
	sf::Sprite m_sprite;

//Components
	std::unique_ptr<Components::MovementComponent>  m_movementСomponent;
	std::unique_ptr<Components::AnimationComponent> m_animationСomponent;
	std::unique_ptr<Components::HitboxComponent>    m_hitboxComponent;

//Creators
	void createMovementComponent (sf::Sprite& sprite, const float& maxSpeed, const float& acceleration, const float& deceleration);
	void createAnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	void createHitboxComponent   (sf::Sprite& sprite, const sf::Vector2f& offset_xy, const sf::Vector2f& size_xy, const sf::Vector2f& scale = sf::Vector2f(1.f, 1.f));
};
} //!namespace Entities
#endif //!ENTITY_H