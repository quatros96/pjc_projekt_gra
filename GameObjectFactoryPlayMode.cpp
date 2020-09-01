
#include "GameObjectFactoryPlayMode.h"
#include <iostream>
#include "TransformComponent.h"
#include "StandardGraphicsComponent.h"
#include "PlayerUpdateComponent.h"
#include "RectColliderComponent.h"
#include "InvaderUpdateComponent.h"
#include "BulletUpdateComponent.h"
#include "AnimatedGraphicsComponent.h"

void GameObjectFactoryPlayMode::buildGameObject(GameObjectBlueprint &bp, std::vector<GameObject> &gameObjects)
{
    GameObject gameObject;
    gameObject.setTag(bp.getName());
    for(auto element : bp.getComponentList())
    {
        std::cout << element;
        std::cout << std::endl;
    }
	bp.getComponentList();
    auto it = bp.getComponentList().begin();
    auto end = bp.getComponentList().end();
    for(it; it != end; it++)
    {
        if(*it == "Transform")
        {
            gameObject.addComponent(std::make_shared<TransformComponent>(
                    bp.getWidth(), bp.getHeight(), sf::Vector2f(bp.getLacationX(), bp.getLocationY()),
                    bp.getSpeed()));
        }
        else if(*it == "Player Update")
        {
            gameObject.addComponent(std::make_shared<PlayerUpdateComponent>());
        }
        else if(*it == "Invader Update")
        {
            gameObject.addComponent(std::make_shared<InvaderUpdateComponent>());
        }
        else if(*it == "Bullet Update")
        {
            gameObject.addComponent(std::make_shared<BulletUpdateComponent>());
        }
        else if(*it == "Standard Graphics")
        {
            std::shared_ptr<StandardGraphicsComponent> sgp =
                    std::make_shared<StandardGraphicsComponent>();
            gameObject.addComponent(sgp);
            sgp->initializeGraphics(bp.getBitmapName(),
                    sf::Vector2f(bp.getWidth(), bp.getHeight()));
        }
        else if(*it == "Animated Graphics")
        {
            std::shared_ptr<AnimatedGraphicsComponent> agp =
                std::make_shared<AnimatedGraphicsComponent>();
            gameObject.addComponent(agp);
            agp->initializeGraphics(bp.getBitmapName(),
                sf::Vector2f(bp.getWidth(), bp.getHeight()));
        }
    }
    if(bp.getEncompassingRectCollider())
    {
        std::shared_ptr<RectColliderComponent> rcc =
                std::make_shared<RectColliderComponent>(bp.getEncompassingRectColliderLabel(), bp.getWidthOffset(), bp.getHeightOffset());
        gameObject.addComponent(rcc);
        rcc->setOrMoveCollider(bp.getLacationX(), bp.getLocationY(), bp.getWidth(), bp.getHeight());
    }
    gameObject.setObjectAnimations(bp.getAnimations());
    gameObjects.push_back(gameObject);
}