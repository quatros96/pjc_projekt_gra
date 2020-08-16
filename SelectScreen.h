//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_SELECTSCREEN_H
#define GRA_SPACE_INVADERS_SELECTSCREEN_H

#include "Screen.h"
class SelectScreen : public Screen
{
private:
    ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
    sf::Texture m_BackgroundTexture;
    sf::Sprite m_BackgroundSprite;
public:
    SelectScreen(ScreenManagerRemoteControl* smrc, sf::Vector2i res);
    void virtual draw(sf::RenderWindow& window);
};

#endif //GRA_SPACE_INVADERS_SELECTSCREEN_H
