#include "TexturePicker.h"

#include <iostream>

#include "WorldState.h"

TexturePicker::TexturePicker(float x, float y, float width, float height, sf::Texture& texture_sheet)
{
	hidden = false;
	bounds.setSize(sf::Vector2f(width, height));
	bounds.setPosition(x, y);
	bounds.setFillColor(sf::Color(50, 50, 50, 130));
	bounds.setOutlineThickness(1.f);
	bounds.setOutlineColor(sf::Color(250, 250, 250, 200));

	sheet.setTexture(texture_sheet);
	sheet.setPosition(x, y);

	if(sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
	{
		sheet.setTextureRect(sf::IntRect(0, 0, bounds.getGlobalBounds().width, sheet.getGlobalBounds().height));
	}
	if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
	{
		sheet.setTextureRect(sf::IntRect(0, 0, sheet.getGlobalBounds().width, bounds.getGlobalBounds().height));
	}
	tileSelector.setPosition(x, y);
	tileSelector.setSize(sf::Vector2f(WorldState::TILE_SIZE, WorldState::TILE_SIZE));
	tileSelector.setFillColor(sf::Color::Transparent);
	tileSelector.setOutlineThickness(1.f);
	tileSelector.setOutlineColor(sf::Color::Red);
	textureContainer.width = WorldState::TILE_SIZE;
	textureContainer.height = WorldState::TILE_SIZE;

	rect.left = 0;
	rect.top = 0;
}

void TexturePicker::draw(sf::RenderTarget& window)
{
	if(!hidden)
	{
		window.draw(bounds);
		window.draw(sheet);
		if (active)
		{
			window.draw(tileSelector);
		}
	}
	
}

void TexturePicker::update(sf::Vector2f& mousePosWindow)
{
	if(!hidden)
	{
		if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			active = true;
		}
		else
		{
			active = false;
		}
		if (active)
		{
			mousePositionGrid.x = (static_cast<int>(mousePosWindow.x - bounds.getPosition().x)) / WorldState::TILE_SIZE;
			mousePositionGrid.y = static_cast<int>(mousePosWindow.y - bounds.getPosition().y) / WorldState::TILE_SIZE;
			tileSelector.setPosition(bounds.getPosition().x + mousePositionGrid.x * WorldState::TILE_SIZE, bounds.getPosition().y + mousePositionGrid.y * WorldState::TILE_SIZE);
			std::cout << mousePositionGrid.x << "x" << mousePositionGrid.y << std::endl;
			textureContainer.left = tileSelector.getPosition().x - bounds.getPosition().x + rect.left;
			textureContainer.top = tileSelector.getPosition().y - bounds.getPosition().y + rect.top;
		}
	}
	
}

bool& TexturePicker::getActive()
{
	return active;
}

sf::IntRect& TexturePicker::getTextureContainer()
{
	return textureContainer;
}

void TexturePicker::hideOrShow()
{
	hidden = !hidden;
}

void TexturePicker::navigateOnSheet(int x_offset, int y_offset)
{
	if(rect.left + x_offset < 0 || rect.top + y_offset < 0)
	{
		rect.left = 0;
		rect.top = 0;
	}
	
	else
	{
		rect.left += x_offset;
		rect.top += y_offset;
	}
	rect.width = bounds.getGlobalBounds().width;
	rect.height = bounds.getGlobalBounds().height;
	sheet.setTextureRect(rect);
}
