#ifndef PLAYER_H
#define PLAYER_H

#include "stdHeader.hpp"

#include "Entity.hpp"

namespace cog
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
	void update_animations(const float& dt);
	void update_input();

	//Init
	void inline init_animations();
};
} // !namespace cog
#endif // !PLAYER_H