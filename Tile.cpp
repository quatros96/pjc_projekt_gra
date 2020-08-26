#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSize, sf::Texture& texture, sf::IntRect selector)
{
	m_Tile.setSize(sf::Vector2f(gridSize, gridSize));
	m_Tile.setPosition(x, y);
	m_Tile.setFillColor(sf::Color::White);
	//m_Tile.setOutlineThickness(1.f);
	//m_Tile.setOutlineColor(sf::Color::Magenta);
	m_Tile.setTexture(&texture);
	m_Tile.setTextureRect(selector);
	
}

void Tile::draw(sf::RenderTarget& window)
{
	window.draw(m_Tile);
}

void Tile::update()
{
	
}

sf::RectangleShape& Tile::getTile()
{
	return m_Tile;
}
