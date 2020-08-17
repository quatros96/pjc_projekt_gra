#pragma once
#include "Screen.h"
#include "Button.h"
class EditorScreen :
    public Screen
{
private:
	sf::Font font;
	ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
public:
	EditorScreen(ScreenManagerRemoteControl* smrc, sf::Vector2i res);
	void draw(sf::RenderWindow& window);
};

