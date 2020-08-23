#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
class TileMap
{
private:
	float m_GridSizeF;
	unsigned m_GridSize;
	sf::Vector2u m_MapSize;
	unsigned m_NumOfLayers;
	std::vector<std::vector<std::vector<Tile>>> m_Map;
public:
	TileMap();
	void update();
	void draw(sf::RenderTarget& window);
};

