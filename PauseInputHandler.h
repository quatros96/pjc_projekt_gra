#pragma once

#include "InputHandler.h"
class PauseInputHandler :
    public InputHandler
{
public:
    void HandleKeyPressed(sf::Event& event, sf::RenderWindow& window) override;
    void handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window) override;
};

