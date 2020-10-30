#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

namespace Components
{
class HitboxComponent
{
public:
//Constructors
	HitboxComponent(sf::Sprite& sprite,
					const sf::Vector2f& m_offsetBasic,
					const sf::Vector2f& size_xy,
					const sf::Vector2f& scale = sf::Vector2f(1.f, 1.f)
	);
	~HitboxComponent();

//Accessors
	sf::Vector2f GetDefaultSize() const;

//Modificators
	void SetPosition(const sf::Vector2f& position);
	void SetOffsetMove(const sf::Vector2f& offset);
	void SetRotation(const float& rotation);
	void SetSize(const sf::Vector2f& size);

//Functions
	bool СheckIntersect(const sf::FloatRect& rect);

//Update and Render
	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
private:
	//Members
	sf::Sprite& m_sprite;
	sf::RectangleShape m_hitbox;
	sf::Vector2f m_defaultSize;

	sf::Vector2f m_offsetBasic;
	sf::Vector2f m_offsetMove;
};
} // !namespace Components
#endif // !HITBOX_COMPONENT_H