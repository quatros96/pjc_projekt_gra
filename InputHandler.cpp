//
// Created by quatr on 22.04.2020.
//

#include "InputHandler.h"
#include <sstream>

void InputHandler::initialiseInputHandler(ScreenManagerRemoteControl *sw, std::vector<std::shared_ptr<Button>> buttons, sf::View *pointerToUIView, Screen *parentScreen)
{
    m_ScreenManagerRemoteControl = sw;
    m_Buttons = buttons;
    m_PointerToUIPanelView = pointerToUIView;
    m_ParenScreen = parentScreen;
}
void InputHandler::handleInput(sf::RenderWindow &window, sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        HandleKeyPressed(event, window);
    }
    if(event.type == sf::Event::KeyReleased)
    {
        handleKeyReleased(event, window);
    }
	//handle hover and left click
    auto end = m_Buttons.end();
    for (auto i = m_Buttons.begin(); i != end; i++)
    {
        if ((*i)->m_Collider.contains(window.mapPixelToCoords(sf::Mouse::getPosition(),
            (*getPointerToUIView()))))
        {
            (*i)->getButton().setFillColor(sf::Color::Black);
        	if(event.type ==sf::Event::MouseButtonReleased)
        	{
                handleLeftClick((*i)->m_Text, window);
                break;
        	}
        }
        else
        {
            (*i)->getButton().setFillColor(sf::Color::Green);
        }
    }
    handleGamepad();
}

void InputHandler::activate()
{
    active = true;
}

void InputHandler::deactivate()
{
    active = false;
}

bool InputHandler::isActive()
{
    return active;
}

void InputHandler::handleGamepad() {};
void InputHandler::HandleKeyPressed(sf::Event &event, sf::RenderWindow &window) {};
void InputHandler::handleKeyReleased(sf::Event &event, sf::RenderWindow &window) {};
void InputHandler::handleLeftClick(std::string &buttonInteractedWith, sf::RenderWindow &window) {};
sf::View* InputHandler::getPointerToUIView()
{
    return m_PointerToUIPanelView;
}
ScreenManagerRemoteControl* InputHandler::getPointerToScreenManagerRemoteControl()
{
    return m_ScreenManagerRemoteControl;
}
Screen* InputHandler::getmParentScreen()
{
    return m_ParenScreen;
}