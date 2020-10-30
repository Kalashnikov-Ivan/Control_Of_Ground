#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"

namespace Entities
{
class Player :
	public Entity
{
public:
//Constructors
	Player(const sf::Vector2f& position_xy, sf::Texture& texture,
		   const float& maxSpeed, const float& acceleration, const float& deceleration,
		   const sf::Vector2f& scale = sf::Vector2f(1.f, 1.f)
	);
	~Player();

//Info
	std::string GetStringInfo() override;

//Functions
	void Move(const sf::Vector2f& dir_xy, const float& dt) override;

//Update and Render
	void Update(const float& dt) override;
	void Render(sf::RenderTarget& target) override;

private:
//Members
	float m_scale_x;
	float m_scale_y;

	bool m_attacking;

//Update
	void UpdateAnimations(const float& dt);
	void UpdateInput();

//Init
	void inline InitAnimations();
};
} // !namespace cog
#endif // !PLAYER_H