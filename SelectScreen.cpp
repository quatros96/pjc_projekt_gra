
#include "SelectScreen.h"
#include "SelectUIPanel.h"
#include "SelectInputHandler.h"

SelectScreen::SelectScreen(ScreenManagerRemoteControl *smrc, sf::Vector2i res)
{
    auto suip = std::make_unique<SelectUIPanel>(res);
    auto sih = std::make_shared<SelectInputHandler>();
    addPanel(std::move(suip), smrc, sih);
    m_ScreenManagerRemoteControl = smrc;
    m_BackgroundTexture.loadFromFile("graphics/background.png");
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
    auto textureSize = m_BackgroundSprite.getTexture()->getSize();
    m_BackgroundSprite.setScale(float(m_View.getSize().x) / textureSize.x,
            float(m_View.getSize().y) / textureSize.y);
    sih->activate();
}
void SelectScreen::draw(sf::RenderWindow &window)
{
    window.setView(m_View);
    window.draw(m_BackgroundSprite);
    Screen::draw(window);
}