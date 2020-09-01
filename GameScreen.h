//
// Created by quatr on 22.04.2020.
//
#pragma once

#include "Screen.h"
#include "GameInputHandler.h"
#include "GameOverInputHandler.h"
#include "BulletSpawner.h"
#include "PhysicsEnginePlayMode.h"
#include "PauseInputHandler.h"
#include "TileMap.h"

class GameScreen : public Screen, public BulletSpawner
{
private:
    ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
    std::shared_ptr<GameInputHandler> m_GIH;
    std::shared_ptr<GameOverInputHandler> m_GOIH;
    std::shared_ptr<PauseInputHandler> m_PIH;
    std::shared_ptr<RectColliderComponent> m_PRCC;
    PhysicsEnginePlayMode m_PhysicsEnginePlayMode;
    int m_NumberInvadersInWorldFile = 0;
    std::vector<int> m_BulletObjectLocations;
    int m_NextBullet = 0;
    bool m_WaitingToSpawnBulletForPlayer = false;
    bool m_WaitingToSpawnBulletForInvader = false;
    sf::Vector2f m_PlayerBulletSpawnLocation;
    sf::Vector2f m_InvaderBulletSpawnLocation;
    sf::Clock m_BulletClock;
    sf::Texture m_BackgroundTexture;
    sf::Sprite m_BackgroundSprite;
    std::shared_ptr<TileMap> m_map;
    sf::RenderTexture m_renderTexture;
    sf::Sprite m_renderSprite;
	
	//functions
    void initPreRender();
public:
    static bool m_GameOver;
	static bool paused;
    GameScreen(ScreenManagerRemoteControl* smrc, sf::Vector2i res);
    void initalise() override;
    void virtual update(float fps);
    void virtual draw(sf::RenderWindow& window);
    void pause();
    void resume();
    BulletSpawner* getBulletSpawner();
    void spawnBullet(sf::Vector2f spawnLocation, bool forPlayer)
    {
        if(forPlayer)
        {
            sf::Time elapsedTime = m_BulletClock.getElapsedTime();
            if(elapsedTime.asMilliseconds() > 400)
            {
                m_PlayerBulletSpawnLocation.x = spawnLocation.x;
                m_PlayerBulletSpawnLocation.y = spawnLocation.y;
                m_WaitingToSpawnBulletForPlayer = true;
                m_BulletClock.restart();
            }
        }
        else
        {
            m_InvaderBulletSpawnLocation.x = spawnLocation.x;
            m_InvaderBulletSpawnLocation.y = spawnLocation.y;
            m_WaitingToSpawnBulletForInvader = true;
        }
    }
};

