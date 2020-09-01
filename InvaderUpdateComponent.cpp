
#include "InvaderUpdateComponent.h"
#include "BulletSpawner.h"
#include "WorldState.h"
#include "SoundEngine.h"

void InvaderUpdateComponent::update(float fps)
{
    
}

void InvaderUpdateComponent::initializeBulletSpawner(BulletSpawner *bulletSpawner, int randSeed)
{
    m_BulletSpawner = bulletSpawner;
    m_RandSpeed = randSeed;
    srand(m_RandSpeed);
    m_TimeBetweenShots = (rand() % 15 + m_RandSpeed);

}