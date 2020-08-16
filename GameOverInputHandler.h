//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_GAMEOVERINPUTHANDLER_H
#define GRA_SPACE_INVADERS_GAMEOVERINPUTHANDLER_H

#include "InputHandler.h"

class GameOverInputHandler : public InputHandler
{
public:
    void HandleKeyPressed(sf::Event& event, sf::RenderWindow& window) override;
    void handleLeftClick(std::string& buttonInteractedWith, sf::RenderWindow& window) override;
};

#endif //GRA_SPACE_INVADERS_GAMEOVERINPUTHANDLER_H
