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
	//change - now its the copy of select screen, lack of input handler and ui panel
    m_EIH = std::make_shared<EditorInputHandler>();
    auto editorUIP = std::make_unique<EditorUIPanel>(res);
    addPanel(std::move(editorUIP), smrc, m_EIH);
    m_PIH = std::make_shared<PauseInputHandler>();
    auto pauseUIPanel = std::make_unique<PauseUIPanel>(res);
    addPanel(std::move(pauseUIPanel), smrc, m_PIH);
    m_ScreenManagerRemoteControl = smrc;
    editorPaused = false;
    m_View.setSize(1280, 720);
    m_View.setCenter(640, 360);
    font.loadFromFile("fonts/Roboto-Bold.ttf");
    mousePosition.setFont(font);
    mousePosition.setCharacterSize(12);
    mousePosition.setFillColor(sf::Color::Red);
    initTileMap();
    initSelector();
}

void EditorScreen::getMousePosition(sf::RenderWindow& window)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);
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
    window.draw(selectorRect);
    window.draw(mousePosition);
    Screen::draw(window);
}

void EditorScreen::update(float fps)
{

	if(!editorPaused)
	{
        m_PIH->deactivate();
        m_EIH->activate();
        selectorRect.setPosition(sf::Vector2f(mousePosGrid.x * WorldState::TILE_SIZE, mousePosGrid.y * WorldState::TILE_SIZE));
        std::stringstream ss;
        ss << mousePosGrid.x;
        ss << "x";
        ss << mousePosGrid.y;
        mousePosition.setString(ss.str());
        mousePosition.setPosition(sf::Vector2f(mousePosView.x, mousePosView.y + 20));
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
            m_Map->addTile(mousePosGrid.x, mousePosGrid.y, 0);
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
    selectorRect.setFillColor(sf::Color::Transparent);
    selectorRect.setOutlineThickness(1.f);
    selectorRect.setOutlineColor(sf::Color::Green);
}
