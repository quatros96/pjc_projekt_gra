//
// Created by quatr on 21.04.2020.
//

#include "GameEngine.h"

GameEngine::GameEngine()
{
    initSettings();
	if(m_SettingsManager.m_AutoMode)
	{
        m_Resolution.x = sf::VideoMode::getDesktopMode().width;
		m_Resolution.y = sf::VideoMode::getDesktopMode().height;
        m_Window.create(sf::VideoMode(m_Resolution.x, m_Resolution.y),
            "MchtrZombie", sf::Style::Fullscreen);
        m_Window.setFramerateLimit(120);
	}
    else
    {
        m_Resolution.x = m_SettingsManager.m_Resolution.width;
        m_Resolution.y = m_SettingsManager.m_Resolution.height;
        if (m_SettingsManager.m_FullScreen)
        {
            m_Window.create(sf::VideoMode(m_Resolution.x, m_Resolution.y),
                "MchtrZombie", sf::Style::Fullscreen, m_SettingsManager.m_ContextSettings);
        }
        else
        {
            m_Window.create(sf::VideoMode(m_Resolution.x, m_Resolution.y),
                "MchtrZombie", sf::Style::Titlebar | sf::Style::Close,
                m_SettingsManager.m_ContextSettings);
        }
        m_Window.setFramerateLimit(m_SettingsManager.m_FPSLimit);
    }
    m_ScreenManager = std::make_unique<ScreenManager>(
            sf::Vector2i(m_Resolution.x, m_Resolution.y));
}
void GameEngine::run()
{
    while (m_Window.isOpen())
    {
        m_DT = m_Clock.restart();
        m_FPS = m_DT.asSeconds();
        handleInput();
        update();
        draw();
    }
}
void GameEngine::handleInput()
{
    m_ScreenManager->handleInput(m_Window);
}
void GameEngine::update()
{
    m_ScreenManager->update(m_FPS);
}
void GameEngine::draw()
{
    m_Window.clear(sf::Color::Black);
    m_ScreenManager->draw(m_Window);
    m_Window.display();
}

void GameEngine::initSettings()
{
    m_SettingsManager.loadSettings("settings.ini");
}
