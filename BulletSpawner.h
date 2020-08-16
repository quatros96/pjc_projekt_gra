//
// Created by quatr on 27.04.2020.
//

#ifndef GRA_SPACE_INVADERS_BULLETSPAWNER_H
#define GRA_SPACE_INVADERS_BULLETSPAWNER_H

#include <SFML/Graphics.hpp>

class BulletSpawner
{
public:
    virtual void spawnBullet(sf::Vector2f spawnLocation, bool forPlayer) = 0;
};

#endif //GRA_SPACE_INVADERS_BULLETSPAWNER_H
