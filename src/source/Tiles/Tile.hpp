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
	Tile(const sf::Vector2f pos, const sf::Vector2f size_xy, const sf::Texture* texture, const sf::IntRect textureRect,
		const bool border_visible = false);
	~Tile();

	//Accessors
	bool GetBorberVisible() const;

	//Modificators
	void SetBorderVisible(const bool option);

	//Update
	void Update(const float& dt);

protected:
	bool m_borderVisible;

private:

};
} // !namespace Tiles

#endif // !TILE_H