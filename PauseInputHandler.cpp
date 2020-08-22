#include "PauseInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include "GameScreen.h"

void PauseInputHandler::HandleKeyPressed(sf::Event& event, sf::RenderWindow& window)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
    	//back to game
        SoundEngine::playClick();
        GameScreen::paused = false;
    }
}
void PauseInputHandler::handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window)
{
    if (buttonInteractedWith == "Resume")
    {
    	//back to game
        SoundEngine::playClick();
        GameScreen::paused = false;

    }
    else if (buttonInteractedWith == "Main Menu")
    {
    	//go to main menu
        SoundEngine::playClick();
        getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
    }
}