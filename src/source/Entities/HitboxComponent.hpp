#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

namespace Components
{
class HitboxComponent
{
public:
	//Constructors
	HitboxComponent(sf::Sprite& sprite,
					const sf::Vector2f& m_offset_basic,
					const sf::Vector2f& size_xy,
					const sf::Vector2f& scale = sf::Vector2f(1.f, 1.f));
	~HitboxComponent();

	//Accessors
	sf::Vector2f getDefaultSize() const;

	//Modificators
	void setPosition(const sf::Vector2f& position);
	void setOffsetMove(const sf::Vector2f& offset);
	void setRotation(const float& rotation);
	void setSize(const sf::Vector2f& size);

	//Functions
	bool checkIntersect(const sf::FloatRect& f_rect);

	//Update and render
	void update(const float& dt);
	void render(sf::RenderTarget& target);
private:
	//Members
	sf::Sprite& m_sprite;
	sf::RectangleShape m_hitbox;
	sf::Vector2f m_default_size;

	sf::Vector2f m_offset_basic;
	sf::Vector2f m_offset_move;
};
} // !namespace Components
#endif // !HITBOX_COMPONENT_H