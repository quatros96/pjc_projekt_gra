#include "EditorUIPanel.h"
#include "TexturePicker.h"

EditorUIPanel::EditorUIPanel(sf::Vector2i res) : UIPanel(res, (res.x / 10) * 5, 1, (res.x / 10) * 3, res.y / 12,
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
void EditorUIPanel::initialiseButtons()
{
    addButton(m_ButtonPadding, m_ButtonPadding, m_ButtonWidth, m_ButtonHeight,
        0, 255, 0, "Save");
    addButton(m_ButtonPadding * 2 + m_ButtonWidth, m_ButtonPadding, m_ButtonWidth, m_ButtonHeight,
        0, 255, 0, "Load");
	
}

void EditorUIPanel::draw(sf::RenderWindow& window)
{
    if (!TexturePicker::hidden)
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
