#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Tile.hpp"

class TileMap
{
public:
	TileMap(const sf::Vector2f& grid_size, const sf::Vector2u& max_size, const size_t layers = 1, const bool tiles_border_visible = true);
	~TileMap();

	//Accessors
	bool getTilesBorderVisible() const;

	//Modificators
	void setTilesBorderVisible(const bool option);

	//Update
	void update(const float& dt);

	//Render
	void render(sf::RenderTarget& target);

private:
	sf::Vector2f m_grid_size_f;
	sf::Vector2u m_grid_size_u;
	sf::Vector2u m_max_size;
	size_t m_layers;

	std::vector< std::vector< std::vector<Tile> > > m_map;

	bool m_tiles_border_visible;
};

#endif // !TILE_MAP_H