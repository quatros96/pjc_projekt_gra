//
// Created by quatr on 22.04.2020.
//

#include "GameInputHandler.h"
#include "SoundEngine.h"
#include "GameScreen.h"
class BulletSpawner;

void GameInputHandler::initialize()
{
    m_PUC = std::static_pointer_cast<PlayerUpdateComponent>
            (getPointerToScreenManagerRemoteControl()
                     ->shareGameObjectSharer()
                     .findFirstObjectWithTag("Player")
                     .getComponentByTypeAndSpecificType(
                             "update", "player"));
    m_PTC = getPointerToScreenManagerRemoteControl()->
            shareGameObjectSharer().findFirstObjectWithTag(
            "Player").getTransformComponent();
}
void GameInputHandler::handleGamepad()
{
    float deadZone = 10.0f;
    float x  = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    if (x < deadZone && x > -deadZone)
    {
        x = 0;
    }
    if (y < deadZone && y > -deadZone)
    {
        y = 0;
    }
    m_PUC->updateShipTravelWithController(x, y);
    //B button
    if (sf::Joystick::isButtonPressed(0, 1))
    {
        mBButtonPressed = true;
    }
    if(!sf::Joystick::isButtonPressed(0, 1) && mBButtonPressed)
    {
        mBButtonPressed = false;
        SoundEngine::playShoot();
        sf::Vector2f spawnLocation;
        spawnLocation.x = m_PTC->getLocation().x + m_PTC->getSize().x / 2;
        spawnLocation.y = m_PTC->getLocation().y;
        static_cast<GameScreen*>(getmParentScreen())->spawnBullet(spawnLocation,true);
    }
}
void GameInputHandler::HandleKeyPressed(sf::Event &event, sf::RenderWindow &window)
{
    if(event.key.code == sf::Keyboard::Escape)
    {
    	
        SoundEngine::playClick();
        GameScreen::paused = true;
    }
    else if (event.key.code == sf::Keyboard::Left)
    {
        m_PUC->moveLeft();
    }
    else if (event.key.code == sf::Keyboard::Right)
    {
        m_PUC->moveRight();
    }
    else if(event.key.code == sf::Keyboard::Up)
    {
        m_PUC->moveUp();
    }
    else if(event.key.code == sf::Keyboard::Down)
    {
        m_PUC->moveDown();
    }
    else
    {
        //m_PUC->stopUp();
        //m_PUC->stopDown();
        //m_PUC->stopLeft();
        //m_PUC->stopRight();
    }
}
void GameInputHandler::handleKeyReleased(sf::Event &event, sf::RenderWindow &window)
{
    if(event.key.code == sf::Keyboard::Left)
    {
        m_PUC->stopLeft();
    }
    else if(event.key.code == sf::Keyboard::Right)
    {
        m_PUC->stopRight();
    }
    else if(event.key.code == sf::Keyboard::Up)
    {
        m_PUC->stopUp();
    }
    else if(event.key.code == sf::Keyboard::Down)
    {
        m_PUC->stopDown();
    }
    else if(event.key.code ==sf::Keyboard::Space)
    {
        //shoot a bullet
        //SoundEngine::playShoot();
        //sf::Vector2f spawnLocation;
        //spawnLocation.x = m_PTC->getLocation().x + m_PTC->getSize().x / 2;
        //spawnLocation.y = m_PTC->getLocation().y;
        //static_cast<GameScreen*>(getmParentScreen())->spawnBullet(spawnLocation, true);
        m_PUC->attack();
    }
}