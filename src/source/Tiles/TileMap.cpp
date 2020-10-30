#include "stdafx.h"

#include "TileMap.hpp"

using namespace Tiles;

TileMap::TileMap(
	const sf::Vector2f& gridSize, const sf::Vector2u& tilesQuantity, std::shared_ptr<sf::Texture> sheetTexture,
	const size_t layers, const bool tilesBorderVisible
)
	: m_gridSize_f    { gridSize }
	, m_gridSize_u    { static_cast<sf::Vector2u>(gridSize) }
	, m_tilesQuantity { tilesQuantity }
	, m_layers        { layers }
	, m_map           { std::vector< std::vector< std::vector<Tile*>>>(tilesQuantity.x, std::vector<std::vector<Tile*>>(tilesQuantity.y, std::vector<Tile*>(layers, nullptr) ) ) }
	, m_tilesBorderVisible { tilesBorderVisible }
	, m_sheetTexture  { sheetTexture }
{
}

TileMap::~TileMap()
{
	//#TODO: Make smart_ptr
	for (auto& x : m_map)
		for (auto& y : x)
			for (auto& z : y)
				if (z != nullptr)
					delete z;
}

//Accessors
bool TileMap::GetTilesBorderVisible() const
{
	return m_tilesBorderVisible;
}

//Modificators
void TileMap::SetTilesBorderVisible(const bool option)
{
	m_tilesBorderVisible = option;

	for (size_t x = 0; x < m_tilesQuantity.x; x++)
	{
		for (size_t y = 0; y < m_tilesQuantity.y; y++)
		{
			if (m_map[x][y][0] != nullptr)
				m_map[x][y][0]->SetBorderVisible(option);
		}
	}
}

//Function
void TileMap::AddTile(const unsigned x, const unsigned y, const unsigned z, const sf::Texture* texture, const sf::IntRect& textureRect)
{
	if ((x >= 0 && x < m_gridSize_u.x) && (y >= 0 && y < m_gridSize_u.y))
	{
		if (m_map[x][y][z] == nullptr)
		{
			m_map[x][y][z] = new Tile(sf::Vector2f(m_gridSize_f.x * x, m_gridSize_f.y * y), m_gridSize_f, 
									  texture, textureRect,
									  m_tilesBorderVisible);
		}
	}
}

void TileMap::DeleteTile(const unsigned x, const unsigned y, const unsigned z)
{
	if ((x >= 0 && x < m_gridSize_u.x) && (y >= 0 && y < m_gridSize_u.y))
	{
		if (m_map[x][y][z] != nullptr)
		{
			delete m_map[x][y][z];
			m_map[x][y][z] = nullptr;
		}
	}
}

//Update
void TileMap::Update(const float& dt)
{
}

//Render
void TileMap::Render(sf::RenderTarget& target)
{
	for (auto& x : m_map)
		for (auto& y : x)
			for (auto& z : y)
				if (z != nullptr)
					target.draw(*z);
}

//File
bool TileMap::SaveToFile(const std::string path)
{
	/*#TODO: Saves the entire tilemap to a text-file.
	Format:
	Size x y
	gridSize x y
	layers
	texture file
	All tiles:
	type
	gridPos x y layer
	Texture rect x y
	collision
	tile_specific...
	*/

	std::ofstream out_f { path };
	if (out_f.is_open())
	{
		out_f << "tilesQuantity" << m_tilesQuantity.x << ' ' << m_tilesQuantity.y << '\n';
		out_f << "gridSize "     << m_gridSize_u.x    << ' ' << m_gridSize_u.y    << '\n';
		out_f << "LAYERS "        << m_layers           << '\n';
	}
	else
	{
		std::cerr << "ERROR::TILE_MAP: can't open file " + path + "for save";
		return false;
	}

	return true;
}

bool TileMap::LoadFromFile(const std::string path)
{
	std::ifstream in_f{ path };
	if (in_f.is_open())
	{

	}
	else
	{
		std::cerr << "ERROR::TILE_MAP: can't open file " + path + "for load";
		return false;
	}

	return true;
}