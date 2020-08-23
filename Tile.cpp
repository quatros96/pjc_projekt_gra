#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSize)
{
	m_Tile.setSize(sf::Vector2f(gridSize, gridSize));
	m_Tile.setFillColor(sf::Color::White);
	m_Tile.setPosition(x, y);
}

void Tile::draw(sf::RenderTarget& window)
{
	window.draw(m_Tile);
}

void Tile::update()
{
	
}
