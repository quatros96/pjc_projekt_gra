#include "EditorInputHandler.h"
#include "EditorScreen.h"
#include "SoundEngine.h"
#include "TexturePicker.h"

bool TexturePicker::hidden;
bool EditorScreen::savingMap;
bool EditorScreen::loadingMap;
bool EditorScreen::m_collision;
int EditorScreen::m_type;
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
	if(event.key.code == sf::Keyboard::Q)
	{
        TexturePicker::hidden = !TexturePicker::hidden;
	}
    else if (event.key.code == sf::Keyboard::C)
    {
        EditorScreen::m_collision = !EditorScreen::m_collision;
    }
    else if (event.key.code == sf::Keyboard::T)
    {
    	if(EditorScreen::m_type == 3)
    	{
            EditorScreen::m_type = 0;
    	}
        else
        {
            EditorScreen::m_type++;
        }
    }
}

void EditorInputHandler::handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window)
{
    if (buttonInteractedWith == "Save")
    {
        //saving map
        SoundEngine::playClick();
        EditorScreen::savingMap = true;
    }
	else if (buttonInteractedWith == "Load")
	{
        SoundEngine::playClick();
        EditorScreen::loadingMap = true;
	}
}
