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
	Player(sf::Vector2f position_xy, sf::Texture* texture);
	~Player();

	//Functions

private:
	//Members

};
} // !namespace cog
#endif // !PLAYER_H