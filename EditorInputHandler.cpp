#include "EditorInputHandler.h"
#include "EditorScreen.h"
#include "SoundEngine.h"

void EditorInputHandler::initialize()
{
	
}

void EditorInputHandler::HandleKeyPressed(sf::Event& event, sf::RenderWindow& window)
{
    if (event.key.code == sf::Keyboard::Escape)
    {

        SoundEngine::playClick();
        EditorScreen::editorPaused = true;
    }
    else if (event.key.code == sf::Keyboard::Left)
    {
    }
    else if (event.key.code == sf::Keyboard::Right)
    {
    }
    else if (event.key.code == sf::Keyboard::Up)
    {
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
    }
    else
    {
    }
}

void EditorInputHandler::handleKeyReleased(sf::Event& event, sf::RenderWindow& window)
{
	
}

void EditorInputHandler::handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window)
{
	
}