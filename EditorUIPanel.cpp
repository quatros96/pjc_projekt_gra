#include "EditorUIPanel.h"

EditorUIPanel::EditorUIPanel(sf::Vector2i res) : UIPanel(res, 1, 1, res.x / 3, res.y / 12,
	50, 255, 255, 255)
{
	
}

void EditorUIPanel::draw(sf::RenderWindow& window)
{
	UIPanel::draw(window);
}
