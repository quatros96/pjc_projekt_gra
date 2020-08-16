//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_GAMEOVERUIPANEL_H
#define GRA_SPACE_INVADERS_GAMEOVERUIPANEL_H

#include "UIPanel.h"

class GameOverUIPanel : public UIPanel
{
private:
    void initialiseButtons();

public:
    GameOverUIPanel(sf::Vector2i res);
    void virtual draw(sf::RenderWindow& window);
};


#endif //GRA_SPACE_INVADERS_GAMEOVERUIPANEL_H
