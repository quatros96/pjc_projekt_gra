//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_INPUTHANDLER_H
#define GRA_SPACE_INVADERS_INPUTHANDLER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Button.h"
#include "Screen.h"
#include "ScreenManagerRemoteControl.h"

class Screen;
class InputHandler
{
private:
    Screen* m_ParenScreen;
    std::vector<std::shared_ptr<Button>> m_Buttons;
    sf::View* m_PointerToUIPanelView;
    ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
public:
    void initialiseInputHandler(ScreenManagerRemoteControl* sw,std::vector<std::shared_ptr<Button>> buttons,
            sf::View* pointerToUIView, Screen* parentScreen);
    void handleInput(sf::RenderWindow& window, sf::Event& event);
    virtual void handleGamepad();
    virtual void HandleKeyPressed(sf::Event& event, sf::RenderWindow& window);
    virtual void handleKeyReleased(sf::Event& event, sf::RenderWindow& window);
    virtual void handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window);
    sf::View* getPointerToUIView();
    ScreenManagerRemoteControl* getPointerToScreenManagerRemoteControl();
    Screen* getmParentScreen();
};

#endif //GRA_SPACE_INVADERS_INPUTHANDLER_H
