#pragma once
#include "InputHandler.h"
class EditorInputHandler :
    public InputHandler
{
private:
public:
    void initialize();
    void HandleKeyPressed(sf::Event& event, sf::RenderWindow& window) override;
    void handleKeyReleased(sf::Event& event, sf::RenderWindow& window) override;
    void handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window) override;
};

