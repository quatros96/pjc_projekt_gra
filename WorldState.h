//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_WORLDSTATE_H
#define GRA_SPACE_INVADERS_WORLDSTATE_H

class WorldState
{
public:
    static const int WORLD_WIDTH {640};
    static int WORLD_HEIGHT;
    static const int TILE_SIZE {32};
    static int SCORE;
    static int LIVES;
    static int NUM_INVADERS_AT_START;
    static int NUM_INVADERS;
    static int WAVE_NUMBER;

};

#endif //GRA_SPACE_INVADERS_WORLDSTATE_H
