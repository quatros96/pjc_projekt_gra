#include "PauseInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include "GameScreen.h"
#include "EditorScreen.h"

void PauseInputHandler::HandleKeyPressed(sf::Event& event, sf::RenderWindow& window)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
    	//back to game
        SoundEngine::playClick();
        GameScreen::paused = false;
        EditorScreen::editorPaused = false;
    }
}
void PauseInputHandler::handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window)
{
    if (buttonInteractedWith == "Resume")
    {
    	//back to game
        SoundEngine::playClick();
        GameScreen::paused = false;
        EditorScreen::editorPaused = false;
    }
    else if (buttonInteractedWith == "Main Menu")
    {
    	//go to main menu
        SoundEngine::playClick();
        GameScreen::paused = false;
        EditorScreen::editorPaused = false; 
        getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
    }
}