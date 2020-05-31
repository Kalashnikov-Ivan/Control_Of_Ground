#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

#include "stdHeader.hpp"

namespace Components
{
class HitboxComponent
{
public:
	//Constructors
	HitboxComponent(sf::Sprite& sprite,
					const sf::Vector2f& offset_xy, 
					const sf::Vector2f& size_xy);
	virtual ~HitboxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& f_rect);

	void update(const float& dt);

	void render(sf::RenderTarget& target);
private:
	//Members
	sf::Sprite& m_sprite;
	sf::RectangleShape m_hitbox;

	sf::Vector2f m_offset_xy;
};
} // !namespace Components
#endif // !HITBOX_COMPONENT_H