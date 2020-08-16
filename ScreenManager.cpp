//
// Created by quatr on 21.04.2020.
//

#include "ScreenManager.h"

#include <memory>

ScreenManager::ScreenManager(sf::Vector2i res)
{
    m_Screens["Game"] = std::make_unique<GameScreen>(this, res);
    m_Screens["Select"] = std::make_unique<SelectScreen>(this, res);
}
void ScreenManager::handleInput(sf::RenderWindow &window)
{
    m_Screens[m_CurrentScreen]->handleInput(window);
}
void ScreenManager::update(float fps)
{
    m_Screens[m_CurrentScreen]->update(fps);
}
void ScreenManager::draw(sf::RenderWindow &window)
{
    m_Screens[m_CurrentScreen]->draw(window);
}