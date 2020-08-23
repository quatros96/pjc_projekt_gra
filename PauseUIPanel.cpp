#include "PauseUIPanel.h"
#include "GameScreen.h"

bool GameScreen::paused;

void PauseUIPanel::initialiseButtons()
{
    addButton(m_ButtonPadding, m_ButtonPadding, m_ButtonWidth, m_ButtonHeight,
        0, 255, 0, "Resume");
    addButton(m_ButtonWidth + (m_ButtonPadding * 2), m_ButtonPadding, m_ButtonWidth * 1.5, m_ButtonHeight,
        255, 0, 0, "Main Menu");
}

PauseUIPanel::PauseUIPanel(sf::Vector2i res):
    UIPanel(res, (res.x / 10) * 3, res.y / 2, (res.x / 10) * 3, res.y / 6,
        50, 255, 255, 255)
{
    m_ButtonWidth = res.x / 10;
    m_ButtonHeight = res.y / 20;
    m_ButtonPadding = res.x / 80;
    m_Text.setFillColor(sf::Color(0, 255, 0, 255));
    m_Text.setString("PAUSED");
    m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
    m_Text.setFont(m_Font);
    m_Text.setPosition(sf::Vector2f(m_ButtonPadding, (m_ButtonPadding * 2) + m_ButtonHeight));
    m_Text.setCharacterSize(60);
    initialiseButtons();
}

void PauseUIPanel::draw(sf::RenderWindow& window)
{
    if (GameScreen::paused)
    {
        show();
        UIPanel::draw(window);
        window.draw(m_Text);
    }
    else
    {
        hide();
    }
}
