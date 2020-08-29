#pragma once
#include "Screen.h"
#include "Button.h"
#include "PauseInputHandler.h"
#include "EditorInputHandler.h"
#include "TileMap.h"
#include "TexturePicker.h"

class EditorScreen :
    public Screen
{
private:
	sf::Font font;
	ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
	std::shared_ptr<PauseInputHandler> m_PIH;
	std::shared_ptr<EditorInputHandler> m_EIH;
	std::shared_ptr<TileMap> m_Map;
	sf::RectangleShape selectorRect;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;
	sf::Text mousePosition;
	sf::IntRect texture_selector;
	sf::Text cursorText;
	std::shared_ptr<TexturePicker> m_TexturePicker;
public:
	static bool editorPaused;
	static bool savingMap;
	static bool loadingMap;
	EditorScreen(ScreenManagerRemoteControl* smrc, sf::Vector2i res);
	void getMousePosition(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void update(float fps);
	void initTileMap();
	void initSelector();
	void initCursorText();
};

