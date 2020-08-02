#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Tile.hpp"

namespace Tiles
{
class TileMap
{
public:
	TileMap(
		const sf::Vector2f& grid_size, const sf::Vector2u& tiles_quantity, std::shared_ptr<sf::Texture> sheet_texture,
		const size_t layers = 1, const bool tiles_border_visible = true
	);
	~TileMap();

	//Accessors
	bool getTilesBorderVisible() const;

	//Modificators
	void setTilesBorderVisible(const bool option);

	//Function
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::Texture* texture, const sf::IntRect& texture_rect);
	void deleteTile(const unsigned x, const unsigned y, const unsigned z);

	void update(const float& dt);
	void render(sf::RenderTarget& target);

	//File
	bool saveToFile(const std::string path);
	bool loadFromFile(const std::string path);

private:
	std::shared_ptr<sf::Texture> m_sheet_texture;

	sf::Vector2f m_grid_size_f;
	sf::Vector2u m_grid_size_u;
	sf::Vector2u m_tiles_quantity;
	size_t m_layers;

	std::vector< std::vector< std::vector<Tile*> > > m_map;

	bool m_tiles_border_visible;
};
} // !namespace Tiles
#endif // !TILE_MAP_H