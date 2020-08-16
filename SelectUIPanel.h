//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_SELECTUIPANEL_H
#define GRA_SPACE_INVADERS_SELECTUIPANEL_H

#include "UIPanel.h"

class SelectUIPanel : public UIPanel
{
private:
    void initialiseButtons();

public:
    SelectUIPanel(sf::Vector2i res);
    void virtual draw(sf::RenderWindow& window);
};

#endif //GRA_SPACE_INVADERS_SELECTUIPANEL_H
