#pragma once
#include "UIPanel.h"
class EditorUIPanel :
    public UIPanel
{
public:
    void initialiseButtons();
    EditorUIPanel(sf::Vector2i res);
    void draw(sf::RenderWindow& window) override;
};

