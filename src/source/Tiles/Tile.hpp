#ifndef TILE_H
#define TILE_H

namespace Tiles
{
class Tile :
	public sf::RectangleShape
{
public:
	//Constructors
	Tile();
	Tile(const sf::Vector2f pos, const sf::Vector2f size_xy, const sf::Texture* texture, const sf::IntRect texture_rect,
		const bool border_visible = false);
	virtual ~Tile();

	//Accessors
	bool getBorberVisible() const;

	//Modificators
	void setBorderVisible(const bool option);

	//Update
	void update(const float& dt);

protected:
	bool m_border_visible;

private:

};
} // !namespace Tiles

#endif // !TILE_H