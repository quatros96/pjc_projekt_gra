//
// Created by quatr on 22.04.2020.
//

#include "GameScreen.h"
#include "GameUIPanel.h"
#include "PauseUIPanel.h"
#include "GameInputHandler.h"
#include "GameOverUIPanel.h"
#include "WorldState.h"
#include "GameObject.h"
#include "BulletUpdateComponent.h"
#include "InvaderUpdateComponent.h"
class BulletSpawner;
int WorldState::WORLD_HEIGHT;
int WorldState::NUM_INVADERS;
int WorldState::NUM_INVADERS_AT_START;

GameScreen::GameScreen(ScreenManagerRemoteControl *smrc, sf::Vector2i res)
{
    m_GIH = std::make_shared<GameInputHandler>();
    auto guip = std::make_unique<GameUIPanel>(res);
    addPanel(std::move(guip), smrc, m_GIH);
    m_GOIH = std::make_shared<GameOverInputHandler>();
    auto gouip = std::make_unique<GameOverUIPanel>(res);
    addPanel(std::move(gouip), smrc, m_GOIH);
    m_PIH = std::make_shared<PauseInputHandler>();
    auto pausedUIP = std::make_unique<PauseUIPanel>(res);
    addPanel(std::move(pausedUIP), smrc, m_PIH);
    m_ScreenManagerRemoteControl = smrc;
    float screenWidth = sf::VideoMode::getDesktopMode().width;
    float screenHeight = sf::VideoMode::getDesktopMode().height;
    float screenRatio = screenWidth / screenHeight;
    WorldState::WORLD_HEIGHT = WorldState::WORLD_WIDTH / screenRatio;
    m_View.setSize(WorldState::WORLD_WIDTH, WorldState::WORLD_HEIGHT);
    m_View.setCenter(sf::Vector2f(WorldState::WORLD_WIDTH / 2,
            WorldState::WORLD_HEIGHT / 2));
    paused = false;
    //m_BackgroundTexture.loadFromFile("graphics/background.png");
    //m_BackgroundSprite.setTexture(m_BackgroundTexture);
    //auto textureSize = m_BackgroundSprite.getTexture()->getSize();
    //m_BackgroundSprite.setScale(float(m_View.getSize().x) / 
    //        float(m_View.getSize().y) / textureSize.y);
}
void GameScreen::initalise()
{
    paused = false;
    m_GIH->initialize();
    m_GIH->activate();
    m_GOIH->deactivate();
    m_PIH->deactivate();
    m_PhysicsEnginePlayMode.initialize(m_ScreenManagerRemoteControl->shareGameObjectSharer());
    WorldState::NUM_INVADERS = 0;
    //store bullets locations and spawn bulletspawner in invaders
    int i {};
    auto it = m_ScreenManagerRemoteControl->getGameObjects().begin();
    auto end = m_ScreenManagerRemoteControl->getGameObjects().end();
    for(it; it != end; it++)
    {
    	
        if(it->getTag() == "bullet")
        {
            m_BulletObjectLocations.push_back(i);
        }
        if((*it).getTag() == "invader")
        {
            std::static_pointer_cast<InvaderUpdateComponent>
                    ((*it).getUpdateComponent())->initializeBulletSpawner(getBulletSpawner(), i);
            WorldState::NUM_INVADERS++;
        }
        i++;
    }
    m_GameOver = false;
    if(WorldState::WAVE_NUMBER == 0)
    {
        WorldState::NUM_INVADERS_AT_START = WorldState::NUM_INVADERS;
        WorldState::WAVE_NUMBER = 1;
        WorldState::LIVES = 3;
        WorldState::SCORE = 0;
    }
}
void GameScreen::update(float fps)
{
	if(!paused)
	{
        m_PIH->deactivate();
        m_GIH->activate();
        if (!m_GameOver)
        {
            if (m_WaitingToSpawnBulletForPlayer)
            {
                std::static_pointer_cast<BulletUpdateComponent>
                    (m_ScreenManagerRemoteControl->
                        getGameObjects()[m_BulletObjectLocations[m_NextBullet]].getUpdateComponent())->
                    spawnForPlayer(m_PlayerBulletSpawnLocation);
                m_WaitingToSpawnBulletForPlayer = false;
                m_NextBullet++;
                if (m_NextBullet == m_BulletObjectLocations.size())
                {
                    m_NextBullet = 0;
                }
            }
            if (m_WaitingToSpawnBulletForInvader)
            {
                std::static_pointer_cast<BulletUpdateComponent>(m_ScreenManagerRemoteControl->
                    getGameObjects()[m_BulletObjectLocations[m_NextBullet]].getUpdateComponent())->
                    spawnForInvader(m_InvaderBulletSpawnLocation);
                m_WaitingToSpawnBulletForInvader = false;
                m_NextBullet++;
                if (m_NextBullet == m_BulletObjectLocations.size())
                {
                    m_NextBullet = 0;
                }
            }
            auto it = m_ScreenManagerRemoteControl->getGameObjects().begin();
            auto end = m_ScreenManagerRemoteControl->getGameObjects().end();
            for (it; it != end; it++)
            {
                (*it).update(fps);
            }
            m_PhysicsEnginePlayMode.detectCollisions(m_ScreenManagerRemoteControl->getGameObjects(),
                m_BulletObjectLocations);
            if (WorldState::NUM_INVADERS <= 0)
            {
                //change
                //WorldState::WAVE_NUMBER++;
                //m_ScreenManagerRemoteControl->loadLevelInPlayMode("testlvl.txt");
            }
            if (WorldState::LIVES <= 0)
            {
                m_GameOver = true;
                m_GIH->deactivate();
                m_GOIH->activate();
            }
        }
	}
    else
    {
	    //paused
        m_GIH->deactivate();
        m_PIH->activate();
    }
    
}
void GameScreen::draw(sf::RenderWindow &window)
{
    window.setView(m_View);
    //window.draw((m_BackgroundSprite));
    //draw gameobject instances
    //map.draw(window);
    auto it = m_ScreenManagerRemoteControl->getGameObjects().begin();
    auto end = m_ScreenManagerRemoteControl->getGameObjects().end();
    for(it; it != end; it++)
    {
        it->draw(window);
    }
    Screen::draw(window);
}

void GameScreen::pause()
{
    paused = true;
}

void GameScreen::resume()
{
    paused = false;
}

BulletSpawner* GameScreen::getBulletSpawner()
{
    return this;
}
