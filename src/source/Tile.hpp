#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	//Constructors
	Tile();
	Tile(const sf::Vector2f pos, const sf::Vector2f size_xy, const bool border_visible = false);
	virtual ~Tile();

	//Accessors
	bool getBorberVisible() const;

	//Modificators
	void setBorderVisible(const bool option);

	//Update
	void update(const float& dt);

	//Render
	void render(sf::RenderTarget& target);

protected:
	sf::RectangleShape m_shape;

	bool m_border_visible;

private:

};

#endif // !TILE_H