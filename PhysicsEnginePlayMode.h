//
// Created by quatr on 27.04.2020.
//
#pragma once

#include "GameObjectSharer.h"
#include "PlayerUpdateComponent.h"
#include "TileMap.h"
#include "RectColliderComponent.h"
#include "TransformComponent.h"

class PhysicsEnginePlayMode
{
private:
    std::shared_ptr<PlayerUpdateComponent> m_PUC;
    std::shared_ptr<RectColliderComponent> m_PRCC;
    std::shared_ptr<TransformComponent> m_PTC;
    GameObject* m_Player;
    bool m_InvaderHitWallThisFrame {false};
    bool m_InvaderHitWallPreviousFrame {false};
    bool m_NeedToDropDownAndReverse {false};
    bool m_CompletedDropDownAndReverse {false};
    void detectInvaderCollisions(std::vector<GameObject>& objects,
            const std::vector<int>& bulletPositions);
    void detectPlayerCollisionsAndInvaderDirection(std::vector<GameObject>& objects,
            const std::vector<int>& bulletPositions);
    void handlePlayerWorldCollisions(std::vector<GameObject>& objects, std::shared_ptr<TileMap> map);
    void handlePlayerWorldEdgeCollisions();
    //variables for collision detection
    int x_start, x_end, y_start, y_end, layer;
public:
    void initialize(GameObjectSharer& gos);
    void detectCollisions(std::vector<GameObject>& objects,
         const std::vector<int>& bulletPositions, std::shared_ptr<TileMap> map);
};

