//
// Created by quatr on 22.04.2020.
//

#include "Screen.h"

void Screen::initalise() {};
void Screen::addPanel(std::unique_ptr<UIPanel> p,
        ScreenManagerRemoteControl *smrc, std::shared_ptr<InputHandler> ih)
{
    ih->initialiseInputHandler(smrc, p->getButtons(), &p->m_View, this);
    m_Panels.push_back(std::move(p));
    m_InputHandlers.push_back(ih);
}
void Screen::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    auto itr = m_InputHandlers.begin();
    auto end = m_InputHandlers.end();
    while(window.pollEvent(event))
    {
        for(itr; itr != end; itr++)
        {
        	if((*itr)->isActive())
        	{
                (*itr)->handleInput(window, event);
        	}
        }
    }
}

void Screen::update(float fps) {};
void Screen::draw(sf::RenderWindow &window)
{
    auto itr = m_Panels.begin();
    auto end = m_Panels.end();
    for(itr; itr != end; itr++)
    {
        (*itr)->draw(window);
    }
}