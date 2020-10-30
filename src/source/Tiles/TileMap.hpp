#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Tile.hpp"

namespace Tiles
{
class TileMap
{
public:
	TileMap(
		const sf::Vector2f& gridSize, const sf::Vector2u& tilesQuantity, std::shared_ptr<sf::Texture> sheetTexture,
		const size_t layers = 1, const bool tilesBorderVisible = true
	);
	~TileMap();

	//Accessors
	bool GetTilesBorderVisible() const;

	//Modificators
	void SetTilesBorderVisible(const bool option);

	//Function
	void AddTile(const unsigned x, const unsigned y, const unsigned z, const sf::Texture* texture, const sf::IntRect& textureRect);
	void DeleteTile(const unsigned x, const unsigned y, const unsigned z);

	void Update(const float& dt);
	void Render(sf::RenderTarget& target);

	//File
	bool SaveToFile(const std::string path);
	bool LoadFromFile(const std::string path);

private:
	std::shared_ptr<sf::Texture> m_sheetTexture;

	sf::Vector2f m_gridSize_f;
	sf::Vector2u m_gridSize_u;
	sf::Vector2u m_tilesQuantity;
	size_t m_layers;

	//#TODO: Make smart_ptr
	std::vector< std::vector< std::vector<Tile*> > > m_map;

	bool m_tilesBorderVisible;
};
} // !namespace Tiles
#endif // !TILE_MAP_H