#pragma once
#include <SFML/Graphics.hpp>
class Tile
{
private:
protected:
	sf::RectangleShape m_Tile;
public:
	Tile();
	Tile(float x, float y, float gridSize);
	void draw(sf::RenderTarget& window);
	void update();
	sf::RectangleShape& getTile();
};

