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
		}
	}
	if(!m_TextureSheet.loadFromFile("graphics/" + textureFile))
	{
		std::cout << "Texture loading error!";
	}
	collisionBox.setSize(sf::Vector2f(WorldState::TILE_SIZE, WorldState::TILE_SIZE));
	collisionBox.setOutlineColor(sf::Color(255, 0, 0, 100));
	collisionBox.setFillColor(sf::Color::Transparent);
	collisionBox.setOutlineThickness(-1.f);
}

void TileMap::draw(sf::RenderTarget& window, sf::Vector2u playerPosGrid, bool showColliders)
{
	//getting render bounds
	x_start = playerPosGrid.x - 19;
	x_end = playerPosGrid.x + 20;
	y_start = playerPosGrid.y - 19;
	y_end = playerPosGrid.y + 20;
	layer = 0;
	if (x_start < 0)
	{
		x_start = 0;
	}
	if (x_end > getMapSize().x)
	{
		x_end = getMapSize().x;
	}
	if (y_start < 0)
	{
		y_start = 0;
	}
	if (y_end > getMapSize().y)
	{
		y_end = getMapSize().y;
	}

	for (int x = x_start; x < x_end; x++)
	{
		for (int y = y_start; y < y_end; y++)
		{
			for (size_t k = 0; k < m_Map[x][y].size(); k++)
			{
				if(m_Map[x][y][k]->getType() == ONTOP)
				{
					lateRenderStack.push(m_Map[x][y][k]);
				}
				else
				{
					m_Map[x][y][k]->draw(window);
				}
				if (m_Map[x][y][k]->getCollisionStatus() && showColliders)
				{
					collisionBox.setPosition(m_Map[x][y][k]->getTilePosition());
					window.draw(collisionBox);
				}
			}
		}
	}
}

void TileMap::addTile(unsigned x, unsigned y, unsigned layer, sf::IntRect selector, bool colision, int type)
{
	if(x < m_MapSize.x && y < m_MapSize.y && layer < m_NumOfLayers)
	{
		m_Map[x][y].push_back(std::make_shared<Tile>(x * WorldState::TILE_SIZE, y * WorldState::TILE_SIZE, WorldState::TILE_SIZE, m_TextureSheet, selector, colision, type));
	}
}

void TileMap::removeTile(unsigned x, unsigned y, unsigned layer)
{
	if (x < m_MapSize.x && y < m_MapSize.y && layer < m_NumOfLayers)
	{
		if (!m_Map[x][y].empty())
		{
			m_Map[x][y][m_Map[x][y].size() - 1] = nullptr;
			m_Map[x][y].pop_back();
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
				for (int z = 0; z < m_Map[x][y].size(); ++z)
				{
					if(!m_Map[x][y].empty())
					{
						outputFile << x << " " << y << " " << z << " " << m_Map[x][y][z]->getTileAsString() << " ";
					}
				}
			}
		}
		
	}
	else
	{
		std::cout << "could not save m_Map to file!" << std::endl;
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
			}
		}
		if (!m_TextureSheet.loadFromFile("graphics/" + m_TextureFile))
		{
			std::cout << "Texture loading error!";
		}
		while(inputFile >> x >> y >> z >> textureRectX >> textureRecty >> collision >> type)
		{
			m_Map[x][y].push_back(std::make_shared<Tile>(x * m_GridSizeF, y * m_GridSizeF, m_GridSizeF, m_TextureSheet, sf::IntRect(textureRectX, textureRecty, m_GridSize, m_GridSize), collision, type));
		}
	}
	else
	{
		std::cout << "could not save m_Map from file!" << std::endl;
	}
	inputFile.close();
}

sf::Vector2u TileMap::getMapSize()
{
	return m_MapSize;
}

std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>& TileMap::getMap()
{
	return m_Map;
}

void TileMap::lateRenderTiles(sf::RenderTarget& window)
{
	while (!lateRenderStack.empty())
	{
		lateRenderStack.top()->draw(window);
		lateRenderStack.pop();
	}
}
