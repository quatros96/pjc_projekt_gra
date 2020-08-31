#include "SelectUIPanel.h"
#include <iostream>

SelectUIPanel::SelectUIPanel(sf::Vector2i res) :

    //new uipanel creation
    UIPanel(res, res.x / 3, res.y / 3, res.x / 3, res.y / 3,
            50, 255, 255, 255)
{
    m_ButtonWidth = res.x / 20;
    m_ButtonHeight = res.y / 20;
    m_ButtonPadding = res.x / 100;
    m_Text.setFillColor(sf::Color(0, 255, 0, 255));
    m_Text.setString("PROJEKT GRA++");
    m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
    m_Text.setFont(m_Font);
    m_Text.setPosition(sf::Vector2f(m_ButtonPadding, m_ButtonPadding));
    m_Text.setCharacterSize(160);
    initialiseButtons();
}
void SelectUIPanel::initialiseButtons()
{
    float positionX = m_Text.getGlobalBounds().width / 2 - m_ButtonWidth / 2 + m_ButtonPadding;
    float positionY = m_ButtonPadding * 4 + m_Text.getGlobalBounds().height;
    float buttonOffsetY = m_ButtonPadding * 2 + m_ButtonHeight;
    addButton(positionX, positionY, m_ButtonWidth, m_ButtonHeight,
            0, 255, 0, "Play");
    addButton(positionX, positionY + buttonOffsetY, m_ButtonWidth, m_ButtonHeight,
        0, 255, 0, "Editor");
    addButton(positionX, positionY + buttonOffsetY * 2, m_ButtonWidth, m_ButtonHeight,
            255, 0, 0, "Quit");
}
void SelectUIPanel::draw(sf::RenderWindow &window)
{
    show();
    UIPanel::draw(window);
    window.draw(m_Text);
}