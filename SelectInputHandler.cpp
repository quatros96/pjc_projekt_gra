
#include "SelectInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include <iostream>

int WorldState::WAVE_NUMBER;

void SelectInputHandler::HandleKeyPressed(sf::Event &event, sf::RenderWindow &window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
    }

}
void SelectInputHandler::handleLeftClick(std::string &buttonInteractedWith, sf::RenderWindow &window)
{
    if(buttonInteractedWith == "Play")
    {
        SoundEngine::playClick();
        WorldState::WAVE_NUMBER = 0;
        getPointerToScreenManagerRemoteControl()->loadLevelInPlayMode("testlvl.txt");
    }
    if(buttonInteractedWith == "Editor")
    {
        SoundEngine::playClick();
        getPointerToScreenManagerRemoteControl()->SwitchScreens("Editor");
    }
    if(buttonInteractedWith == "Quit")
    {
        SoundEngine::playClick();
        window.close();
    }
}