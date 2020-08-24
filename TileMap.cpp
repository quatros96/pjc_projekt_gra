#include "TileMap.h"
#include "WorldState.h"

TileMap::TileMap(float gridSizeF, unsigned width, unsigned height)
{
	m_GridSizeF = gridSizeF;
	m_GridSize = static_cast<unsigned>(m_GridSizeF);
	m_MapSize.x = width;
	m_MapSize.y = height;
	m_NumOfLayers = 1;

	m_Map.resize(m_MapSize.x);
	for (int x = 0; x < m_MapSize.x; ++x)
	{
		m_Map.emplace_back(std::vector<std::vector<std::shared_ptr<Tile>>>());
		for (int y = 0; y < m_MapSize.y; ++y)
		{
			m_Map[x].resize(m_MapSize.y);
			m_Map[x].emplace_back(std::vector<std::shared_ptr<Tile>>());
			for (int z = 0; z < m_NumOfLayers; ++z)
			{
				m_Map[x][y].resize(m_NumOfLayers);
				m_Map[x][y].push_back(nullptr);
			}
		}
	}
}

void TileMap::draw(sf::RenderTarget& window)
{
	for (auto &x : m_Map)
	{
		for (auto &y : x)
		{
			for (auto &tile : y)
			{
				if(tile != nullptr)
				{
					tile->draw(window);
				}
			}
		}
	}
}

void TileMap::addTile(unsigned x, unsigned y, unsigned layer)
{
	if(x < m_MapSize.x && y < m_MapSize.y && layer < m_NumOfLayers)
	{
		if(m_Map[x][y][layer] == nullptr)
		{
			m_Map[x][y][layer] = std::make_shared<Tile>(x * WorldState::TILE_SIZE, y * WorldState::TILE_SIZE, WorldState::TILE_SIZE);
		}
	}
}

void TileMap::removeTile()
{
}
