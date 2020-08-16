//
// Created by quatr on 21.04.2020.
//

#ifndef GRA_SPACE_INVADERS_SOUNDENGINE_H
#define GRA_SPACE_INVADERS_SOUNDENGINE_H

#include <SFML/Audio.hpp>

class SoundEngine
{
private:
    sf::SoundBuffer m_ShootBuffer;
    sf::SoundBuffer m_PlayerExplodeBuffer;
    sf::SoundBuffer m_InvaderExplodeBuffer;
    sf::SoundBuffer m_ClickBuffer;
    sf::Sound m_ShootSound;
    sf::Sound m_PlayerExplodeSound;
    sf::Sound m_InvaderExplodeSound;
    sf::Sound m_UhSound;
    sf::Sound m_OhSound;
    sf::Sound m_ClickSound;
public:
    SoundEngine();
    static void playShoot();
    static void playPlayerExplode();
    static void playInvaderExplode();
    static void playClick();
    static SoundEngine* m_s_Instance;
};

#endif //GRA_SPACE_INVADERS_SOUNDENGINE_H
