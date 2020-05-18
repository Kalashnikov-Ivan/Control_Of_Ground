#ifndef ENTITY_H
#define ENTITY_H

namespace cog
{
class Entity
{
public:
	//Constructors
	Entity();
	virtual ~Entity();

	//Functiong
	virtual void move(const float& dt, const float dir_x, const float dir_y);
	virtual void move(const float& dt, const sf::Vector2f& dir_vector_xy);


	//Pure virtual
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

protected:
	sf::RectangleShape m_shape;

	//Movement
	float m_movement_speed;

private:

};
} // !namespace cog
#endif // !ENTITY_H