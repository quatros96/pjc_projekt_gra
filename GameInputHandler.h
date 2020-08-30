//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_GAMEINPUTHANDLER_H
#define GRA_SPACE_INVADERS_GAMEINPUTHANDLER_H

#include "InputHandler.h"
#include "PlayerUpdateComponent.h"
#include "TransformComponent.h"

class GameInputHandler : public InputHandler
{
private:
    std::shared_ptr<PlayerUpdateComponent> m_PUC;
    std::shared_ptr<TransformComponent> m_PTC;
    bool mBButtonPressed {false};
public:
    void initialize();
    void handleGamepad() override;
    void HandleKeyPressed(sf::Event& event, sf::RenderWindow& window) override;
    void handleKeyReleased(sf::Event& event, sf::RenderWindow& window) override;
};

#endif //GRA_SPACE_INVADERS_GAMEINPUTHANDLER_H
