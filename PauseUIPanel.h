#pragma once
#include "UIPanel.h"
class PauseUIPanel :
    public UIPanel
{
private:
	void initialiseButtons();
public:
	PauseUIPanel(sf::Vector2i res);
	void virtual draw(sf::RenderWindow& window);
};

