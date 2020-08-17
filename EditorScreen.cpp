#include "EditorScreen.h"
#include "SelectScreen.h"
#include "SelectUIPanel.h"
#include "SelectInputHandler.h"

EditorScreen::EditorScreen(ScreenManagerRemoteControl* smrc, sf::Vector2i res)
{
	//change - now its the copy of select screen, lack of input handler and ui panel
    auto suip = std::make_unique<SelectUIPanel>(res);
    auto sih = std::make_shared<SelectInputHandler>();
    addPanel(std::move(suip), smrc, sih);
    m_ScreenManagerRemoteControl = smrc;
}

void EditorScreen::draw(sf::RenderWindow& window)
{
    window.setView(m_View);
    Screen::draw(window);
}
