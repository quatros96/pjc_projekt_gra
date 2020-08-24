#pragma once
#include "UIPanel.h"
class EditorUIPanel :
    public UIPanel
{
public:
    EditorUIPanel(sf::Vector2i res);
    void draw(sf::RenderWindow& window) override;
};

