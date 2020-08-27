#pragma once
#include "SFML/Graphics.hpp"
class TexturePicker
{
private:
	sf::RectangleShape bounds;
	sf::Sprite sheet;
	sf::RectangleShape tileSelector;
	bool active = false;
	sf::Vector2u mousePositionGrid;
	sf::IntRect textureContainer;
	sf::IntRect rect;
public:
	static bool hidden;
	TexturePicker(float x, float y, float width, float height, sf::Texture& texture_sheet);
	void draw(sf::RenderTarget& window);
	void update(sf::Vector2f& mousePosWindow);
	bool& getActive();
	sf::IntRect& getTextureContainer();
	void hideOrShow();
	void navigateOnSheet(int x_offset, int y_offset);
};

