#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
#include "SoundEngine.h"
#include "SettingsManager.h"

class GameEngine
{
private:
    sf::Clock m_Clock;
    sf::Time m_DT;
    sf::RenderWindow m_Window;
    std::unique_ptr<ScreenManager> m_ScreenManager;
    SettingsManager m_SettingsManager;
	
    float m_FPS {};
    sf::Vector2f m_Resolution;
    void handleInput();
    void update();
    void draw();

public:
    void initSettings();
    SoundEngine m_SoundEngine;
    GameEngine();
    void run();
};
