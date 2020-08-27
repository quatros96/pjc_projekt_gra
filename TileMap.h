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
	std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> m_Map;
	sf::Texture m_TextureSheet;
public:
	TileMap(float gridSizeF, unsigned width, unsigned height);
	void update();
	void draw(sf::RenderTarget& window);
	void addTile(unsigned x, unsigned y, unsigned layer, sf::IntRect selector);
	void removeTile(unsigned x, unsigned y, unsigned layer);
	sf::Texture& getTileSheet();
};