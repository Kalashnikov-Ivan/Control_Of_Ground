#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	//Constructors
	Tile();
	Tile(const sf::Vector2f pos, const sf::Vector2f size_xy);
	virtual ~Tile();

	//Update
	void update(const float& dt);

	//Render
	void render(sf::RenderTarget& target);

protected:
	sf::RectangleShape m_shape;

private:

};

#endif // !TILE_H