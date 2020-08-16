//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_UIPANEL_H
#define GRA_SPACE_INVADERS_UIPANEL_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Button.h"

class UIPanel
{
private:
    sf::RectangleShape m_UIPanel;
    bool m_Hidden {false};
    std::vector<std::shared_ptr<Button>> m_Buttons;
protected:
    float m_ButtonWidth {0};
    float m_ButtonHeight {};
    float m_ButtonPadding {};
    sf::Font m_Font;
    sf::Text m_Text;
    void addButton(float x, float y, int width, int height,
            int red, int green, int blue, std::string label);
public:
    sf::View m_View;
    UIPanel(sf::Vector2i res, int x, int y, float width, float height, int alpha,
            int red, int green, int blue);
    std::vector<std::shared_ptr<Button>> getButtons();
    virtual void draw(sf::RenderWindow& window);
    void show();
    void hide();
};

#endif //GRA_SPACE_INVADERS_UIPANEL_H
