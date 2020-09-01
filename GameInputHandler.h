#pragma once

#include "InputHandler.h"
#include "PlayerUpdateComponent.h"
#include "TransformComponent.h"

class GameInputHandler : public InputHandler
{
private:
    std::shared_ptr<PlayerUpdateComponent> m_PUC;
    std::shared_ptr<TransformComponent> m_PTC;
    std::shared_ptr<RectColliderComponent> m_PRCC;
    bool mBButtonPressed {false};
public:
    void initialize();
    void handleGamepad() override;
    void HandleKeyPressed(sf::Event& event, sf::RenderWindow& window) override;
    void handleKeyReleased(sf::Event& event, sf::RenderWindow& window) override;
};
