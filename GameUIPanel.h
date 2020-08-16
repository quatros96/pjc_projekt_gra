//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_GAMEUIPANEL_H
#define GRA_SPACE_INVADERS_GAMEUIPANEL_H

#include "UIPanel.h"

class GameUIPanel : public UIPanel
{
public:
    GameUIPanel(sf::Vector2i res);
    void draw(sf::RenderWindow& window) override;
};

#endif //GRA_SPACE_INVADERS_GAMEUIPANEL_H
