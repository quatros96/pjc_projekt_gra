#include "TileMap.h"

TileMap::TileMap()
{
	m_GridSizeF = 32.f;
	m_GridSize = static_cast<unsigned>(m_GridSizeF);
	m_MapSize.x = 10;
	m_MapSize.y = 10;
	m_NumOfLayers = 1;

	m_Map.resize(m_MapSize.x);
	for (int x = 0; x < m_MapSize.x; ++x)
	{
		m_Map.emplace_back(std::vector<std::vector<Tile>>());
		for (int y = 0; y < m_MapSize.y; ++y)
		{
			m_Map[x].resize(m_MapSize.y);
			m_Map[x].emplace_back(std::vector<Tile>());
			for (int z = 0; z < m_NumOfLayers; ++z)
			{
				m_Map[x][y].resize(m_NumOfLayers);
				m_Map[x][y].push_back(Tile(x * m_GridSizeF, y * m_GridSizeF, m_GridSizeF));
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
				tile.draw(window);
			}
		}
	}
}
