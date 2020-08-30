//
// Created by quatr on 27.04.2020.
//

#ifndef GRA_SPACE_INVADERS_PHYSICSENGINEPLAYMODE_H
#define GRA_SPACE_INVADERS_PHYSICSENGINEPLAYMODE_H

#include "GameObjectSharer.h"
#include "PlayerUpdateComponent.h"
#include "TileMap.h"

class PhysicsEnginePlayMode
{
private:
    std::shared_ptr<PlayerUpdateComponent> m_PUC;
    GameObject* m_Player;
    bool m_InvaderHitWallThisFrame {false};
    bool m_InvaderHitWallPreviousFrame {false};
    bool m_NeedToDropDownAndReverse {false};
    bool m_CompletedDropDownAndReverse {false};
    void detectInvaderCollisions(std::vector<GameObject>& objects,
            const std::vector<int>& bulletPositions);
    void detectPlayerCollisionsAndInvaderDirection(std::vector<GameObject>& objects,
            const std::vector<int>& bulletPositions);
    void handleInvaderDirection();
    void detectPlayerWorldCollisions(std::vector<GameObject>& objects, std::shared_ptr<TileMap> map);

public:
    void initialize(GameObjectSharer& gos);
    void detectCollisions(std::vector<GameObject>& objects,
         const std::vector<int>& bulletPositions, std::shared_ptr<TileMap> map);
};

#endif //GRA_SPACE_INVADERS_PHYSICSENGINEPLAYMODE_H
