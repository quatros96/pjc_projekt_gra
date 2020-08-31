
#include "GameOverInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include <iostream>

void GameOverInputHandler::HandleKeyPressed(sf::Event &event, sf::RenderWindow &window)
{
    if(event.key.code == sf::Keyboard::Escape)
    {
        SoundEngine::playClick();
        getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
    }
}
void GameOverInputHandler::handleLeftClick(std::string &buttonInteractedWith, sf::RenderWindow &window)
{
    if(buttonInteractedWith == "Play")
    {
        SoundEngine::playClick();
        WorldState::WAVE_NUMBER = 0;
        getPointerToScreenManagerRemoteControl()->loadLevelInPlayMode("testlvl.txt");

    }
    else if(buttonInteractedWith == "Home")
    {
        SoundEngine::playClick();
        getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
    }
}
