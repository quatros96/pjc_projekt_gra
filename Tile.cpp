#include "Tile.h"
#include "sstream"

Tile::Tile()
{
	m_collision = false;
	m_type = 0;
}

Tile::Tile(float x, float y, float gridSize, sf::Texture& texture, sf::IntRect selector, bool collision, int type)
{
	m_Tile.setSize(sf::Vector2f(gridSize, gridSize));
	m_Tile.setPosition(x, y);
	m_Tile.setFillColor(sf::Color::White);
	//m_Tile.setOutlineThickness(1.f);
	//m_Tile.setOutlineColor(sf::Color::Magenta);
	m_Tile.setTexture(&texture);
	m_Tile.setTextureRect(selector);
	m_collision = collision;
	m_type = type;
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

std::string Tile::getTileAsString()
{
	std::stringstream ss;
	ss << m_Tile.getTextureRect().left << " " << m_Tile.getTextureRect().top << " " << m_collision << " " << m_type;
	return ss.str();
}
