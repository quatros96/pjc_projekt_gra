//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_SCREEN_H
#define GRA_SPACE_INVADERS_SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "InputHandler.h"
#include "UIPanel.h"
#include "ScreenManagerRemoteControl.h"

class InputHandler;

class Screen
{
private:
    std::vector<std::shared_ptr<InputHandler>> m_InputHandlers;
    std::vector<std::unique_ptr<UIPanel>> m_Panels;
protected:
    void addPanel(std::unique_ptr<UIPanel> p, ScreenManagerRemoteControl* smrc,
            std::shared_ptr<InputHandler> ih);

public:
    virtual void initalise();
    void virtual update(float fps);
    void virtual draw(sf::RenderWindow& window);
    void virtual handleInput(sf::RenderWindow& window);
    sf::View m_View;
};

#endif //GRA_SPACE_INVADERS_SCREEN_H
