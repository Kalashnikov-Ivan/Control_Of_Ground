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

	//Accessors
	float getValueSpeedStageX() const;

	//Update
	void update(const float& dt);

	//Render
	void render(sf::RenderTarget& target);
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