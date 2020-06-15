#include "stdHeader.hpp"

#include "TileMap.hpp"

TileMap::TileMap(const sf::Vector2f& grid_size, const sf::Vector2u& tiles_quantity, const size_t layers, const bool tiles_border_visible)
	: m_grid_size_f { grid_size },
	m_grid_size_u   { static_cast<sf::Vector2u>(grid_size) },
	m_tiles_quantity{ tiles_quantity },
	m_layers        { layers },
	m_map           { std::vector< std::vector< std::vector<Tile*>>>(tiles_quantity.x, std::vector<std::vector<Tile*>>(tiles_quantity.y, std::vector<Tile*>(layers, nullptr) ) ) },
	m_tiles_border_visible { tiles_border_visible }
{
}

TileMap::~TileMap()
{
	for (auto& x : m_map)
		for (auto& y : x)
			for (auto& z : y)
				if (z != nullptr)
					delete z;
}

//Accessors
bool TileMap::getTilesBorderVisible() const
{
	return m_tiles_border_visible;
}

//Modificators
void TileMap::setTilesBorderVisible(const bool option)
{
	m_tiles_border_visible = option;

	for (size_t x = 0; x < m_tiles_quantity.x; x++)
	{
		for (size_t y = 0; y < m_tiles_quantity.y; y++)
		{
			if (m_map[x][y][0] != nullptr)
				m_map[x][y][0]->setBorderVisible(option);
		}
	}
}

//Function
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z)
{
	if ((x >= 0 && x < m_grid_size_u.x) && (y >= 0 && y < m_grid_size_u.y))
	{
		if (m_map[x][y][z] == nullptr)
		{
			m_map[x][y][z] = new Tile(sf::Vector2f(m_grid_size_f.x * x, m_grid_size_f.y * y), m_grid_size_f, m_tiles_border_visible);
		}
	}
}

void TileMap::deleteTile(const unsigned x, const unsigned y, const unsigned z)
{
	if ((x >= 0 && x < m_grid_size_u.x) && (y >= 0 && y < m_grid_size_u.y))
	{
		if (m_map[x][y][z] != nullptr)
		{
			delete m_map[x][y][z];
			m_map[x][y][z] = nullptr;
		}
	}
}

//Update
void TileMap::update(const float& dt)
{
}

//Render
void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : m_map)
		for (auto& y : x)
			for (auto& z : y)
				if (z != nullptr)
					z->render(target);
}