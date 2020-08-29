#include "TileMap.h"

#include <iostream>

#include "WorldState.h"
#include "BitmapStore.h"
#include <fstream>

TileMap::TileMap(float gridSizeF, unsigned width, unsigned height, std::string textureFile)
{
	m_GridSizeF = gridSizeF;
	m_GridSize = static_cast<unsigned>(m_GridSizeF);
	m_MapSize.x = width;
	m_MapSize.y = height;
	m_NumOfLayers = 1;
	m_TextureFile = textureFile;
	m_Map.resize(m_MapSize.x, std::vector<std::vector<std::shared_ptr<Tile>>>());
	for (int x = 0; x < m_MapSize.x; ++x)
	{
		for (int y = 0; y < m_MapSize.y; ++y)
		{
			m_Map[x].resize(m_MapSize.y, std::vector<std::shared_ptr<Tile>>());
			for (int z = 0; z < m_NumOfLayers; ++z)
			{
				m_Map[x][y].resize(m_NumOfLayers, nullptr);
			}
		}
	}
	if(!m_TextureSheet.loadFromFile("graphics/" + textureFile))
	{
		std::cout << "Texture loading error!";
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

void TileMap::addTile(unsigned x, unsigned y, unsigned layer, sf::IntRect selector)
{
	if(x < m_MapSize.x && y < m_MapSize.y && layer < m_NumOfLayers)
	{
		if(m_Map[x][y][layer] == nullptr)
		{
			m_Map[x][y][layer] = std::make_shared<Tile>(x * WorldState::TILE_SIZE, y * WorldState::TILE_SIZE, WorldState::TILE_SIZE, m_TextureSheet, selector);
		}
	}
}

void TileMap::removeTile(unsigned x, unsigned y, unsigned layer)
{
	if (x < m_MapSize.x && y < m_MapSize.y && layer < m_NumOfLayers)
	{
		if (m_Map[x][y][layer] != nullptr)
		{
			m_Map[x][y][layer] = nullptr;
		}
	}
}

sf::Texture& TileMap::getTileSheet()
{
	return m_TextureSheet;
}

void TileMap::saveMap(std::string file_name)
{
	std::ofstream outputFile;
	outputFile.open("world/" + file_name);
	if(outputFile.is_open())
	{
		outputFile << m_MapSize.x << " " << m_MapSize.y << "\n"
			<< m_GridSize << "\n"
			<< m_NumOfLayers << "\n"
			<< m_TextureFile << "\n";
		for (int x = 0; x < m_MapSize.x; ++x)
		{
			for (int y = 0; y < m_MapSize.y; ++y)
			{
				for (int z = 0; z < m_NumOfLayers; ++z)
				{
					if(m_Map[x][y][z] != nullptr)
					{
						outputFile << x << " " << y << " " << z << " " << m_Map[x][y][z]->getTileAsString() << " ";
					}
				}
			}
		}
		
	}
	else
	{
		std::cout << "could not save map to file!" << std::endl;
	}
	outputFile.close();
}

void TileMap::loadMap(std::string file_name)
{
	std::ifstream inputFile;
	inputFile.open("world/" + file_name);
	if (inputFile.is_open())
	{
		sf::Vector2i size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string textureFile;
		unsigned x = 0, y = 0, z = 0;
		unsigned textureRectX = 0, textureRecty = 0;
		bool collision = false;
		int type = 0;
		//world info
		inputFile >> size.x >> size.y >> gridSize >> layers >> textureFile;
		//tiles
		m_GridSizeF = static_cast<float>(gridSize);
		m_GridSize = gridSize;
		m_MapSize.x = size.x;
		m_MapSize.y = size.y;
		m_NumOfLayers = layers;
		m_TextureFile = textureFile;
		m_Map.resize(m_MapSize.x, std::vector<std::vector<std::shared_ptr<Tile>>>());
		for (int x = 0; x < m_MapSize.x; ++x)
		{
			for (int y = 0; y < m_MapSize.y; ++y)
			{
				m_Map[x].resize(m_MapSize.y, std::vector<std::shared_ptr<Tile>>());
				for (int z = 0; z < m_NumOfLayers; ++z)
				{
					m_Map[x][y].resize(m_NumOfLayers, nullptr);
				}
			}
		}
		if (!m_TextureSheet.loadFromFile("graphics/" + m_TextureFile))
		{
			std::cout << "Texture loading error!";
		}
		while(inputFile >> x >> y >> z >> textureRectX >> textureRecty >> collision >> type)
		{
			m_Map[x][y][z] = std::make_shared<Tile>(x * m_GridSizeF, y * m_GridSizeF, m_GridSizeF, m_TextureSheet, sf::IntRect(textureRectX, textureRecty, m_GridSize, m_GridSize), collision, type);
		}
	}
	else
	{
		std::cout << "could not save map from file!" << std::endl;
	}
	inputFile.close();
}
