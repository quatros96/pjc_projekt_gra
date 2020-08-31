#include "Button.h"

Button::Button(sf::Vector2f position, float width, float height, int red, int green, int blue, std::string text)
{
    m_Button.setPosition(position);
    m_Button.setFillColor(sf::Color(red, green, blue));
    m_Button.setSize(sf::Vector2f(width, height));
    m_Text = "" + text;
    m_ButtonText.setCharacterSize(height * 0.7f);
    m_ButtonText.setString(text);
    m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
    m_ButtonText.setFont(m_Font);
    float textPaddingX = (m_Button.getSize().x - m_ButtonText.getGlobalBounds().width) / 2.0f;
    float textPaddingY = 0;
    m_ButtonText.setPosition(sf::Vector2f(
            (position.x + textPaddingX), (position.y + textPaddingY)));
    m_Collider = sf::FloatRect(position, sf::Vector2f(width, height));
}
void Button::draw(sf::RenderWindow &window)
{
    window.draw(m_Button);
    window.draw(m_ButtonText);
}

sf::RectangleShape& Button::getButton()
{
    return m_Button;
}
