#ifndef PLAYER_H
#define PLAYER_H

#include "stdHeader.hpp"

#include "Entity.hpp"

namespace Entities
{
class Player :
	public Entity
{
public:
	//Constructors
	Player(const sf::Vector2f& position_xy, sf::Texture& texture, 
		   const float& max_speed, const float& acceleration, const float& deceleration);
	~Player();

	//Update
	void update(const float& dt);
private:
	//Members

	//Update
	void updateAnimations(const float& dt);
	void updateInput();

	//Init
	void inline initAnimations();
};
} // !namespace cog
#endif // !PLAYER_H