#include "EditorScreen.h"
#include "SelectScreen.h"
#include "SelectUIPanel.h"
#include "SelectInputHandler.h"
#include "PauseUIPanel.h"
#include "EditorUIPanel.h"
#include "WorldState.h"
#include <sstream>

EditorScreen::EditorScreen(ScreenManagerRemoteControl* smrc, sf::Vector2i res)
{
	//add ui and input handler
    m_EIH = std::make_shared<EditorInputHandler>();
    auto editorUIP = std::make_unique<EditorUIPanel>(res);
    addPanel(std::move(editorUIP), smrc, m_EIH);
	//add pause ui and input handler
    m_PIH = std::make_shared<PauseInputHandler>();
    auto pauseUIPanel = std::make_unique<PauseUIPanel>(res);
    addPanel(std::move(pauseUIPanel), smrc, m_PIH);
	
    m_ScreenManagerRemoteControl = smrc;
    editorPaused = false;
	//view 2x the resolution of the game
    m_View.setSize(1280, 720);
    m_View.setCenter(640, 360);
	//prepare text
    font.loadFromFile("fonts/Roboto-Bold.ttf");
    mousePosition.setFont(font);
    mousePosition.setCharacterSize(12);
    mousePosition.setFillColor(sf::Color::Red);
	//make texture_selector size of 32x32 
    texture_selector = sf::IntRect(0, 0, WorldState::TILE_SIZE, WorldState::TILE_SIZE);
	//init 
    initTileMap();
    initSelector();
}

void EditorScreen::getMousePosition(sf::RenderWindow& window)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);
	//most important - screen is in view mode
    mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    this->mousePosGrid =
        sf::Vector2i(
            (static_cast<int>(mousePosView.x) / WorldState::TILE_SIZE),
            (static_cast<int>(mousePosView.y) / WorldState::TILE_SIZE));    
}

void EditorScreen::draw(sf::RenderWindow& window)
{
    window.setView(m_View);
    getMousePosition(window);
    m_Map->draw(window);
	if(!m_TexturePicker->getActive())
	{
		//if texture sheet is active there is no visual indication of tile under it
        window.draw(selectorRect);
	}
	//drawing panel to choose texture
    m_TexturePicker->draw(window);
	//draw where mouse is in grid cordss
    window.draw(mousePosition);
    Screen::draw(window);
}

void EditorScreen::update(float fps)
{
	if(!editorPaused)
	{
        m_TexturePicker->update(mousePosView);
        m_PIH->deactivate();
        m_EIH->activate();
		if(!m_TexturePicker->getActive())
		{
            selectorRect.setPosition(sf::Vector2f(mousePosGrid.x * WorldState::TILE_SIZE, mousePosGrid.y * WorldState::TILE_SIZE));
            selectorRect.setTextureRect(texture_selector);
		}
        std::stringstream ss;
        ss << mousePosGrid.x;
        ss << "x";
        ss << mousePosGrid.y;
        mousePosition.setString(ss.str());
        mousePosition.setPosition(sf::Vector2f(mousePosView.x, mousePosView.y + 20));
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if(!m_TexturePicker->getActive())
			{
                m_Map->addTile(mousePosGrid.x, mousePosGrid.y, 0, texture_selector);
			}
            else
            {
                texture_selector = m_TexturePicker->getTextureContainer();
            }
		}
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if (!m_TexturePicker->getActive())
            {
                m_Map->removeTile(mousePosGrid.x, mousePosGrid.y, 0);
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (!m_TexturePicker->hidden)
            {
                m_TexturePicker->navigateOnSheet(0, 32);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (!m_TexturePicker->hidden)
            {
                m_TexturePicker->navigateOnSheet(0, -32);
            }
        }
	}
    else
    {
        m_PIH->activate();
        m_EIH->deactivate();
    }
}

void EditorScreen::initTileMap()
{
	//hard coded values
    m_Map = std::make_shared<TileMap>(32, 15, 15);
}

void EditorScreen::initSelector()
{
	//size of grid cell
    selectorRect.setSize(sf::Vector2f(32, 32));
    selectorRect.setFillColor(sf::Color(255, 255, 255, 100));
    selectorRect.setOutlineThickness(1.f);
    selectorRect.setOutlineColor(sf::Color::Green);
    selectorRect.setTexture(&m_Map->getTileSheet());
    selectorRect.setTextureRect(texture_selector);

    m_TexturePicker = std::make_shared<TexturePicker>(0, 0, 8 * 32, 320, m_Map->getTileSheet());
}

void EditorScreen::initCursorText()
{
}
