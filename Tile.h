#pragma once
#include <SFML/Graphics.hpp>

enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile
{
private:
protected:
	sf::RectangleShape m_Tile;
	unsigned m_type;
	bool m_collision;
public:
	Tile();
	Tile(float x, float y, float gridSize, sf::Texture& texture, sf::IntRect selector, bool collision = false, int type = TileTypes::DEFAULT);
	void draw(sf::RenderTarget& window);
	void update();
	sf::RectangleShape& getTile();
	std::string getTileAsString();
	const sf::Vector2f& getTilePosition();
	const bool getCollisionStatus();
	const bool intersects(sf::FloatRect objectRect);
	sf::FloatRect getBounds();
};

