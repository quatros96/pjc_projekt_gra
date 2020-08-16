//
// Created by quatr on 22.04.2020.
//

#ifndef GRA_SPACE_INVADERS_SCREENMANAGERREMOTECONTROL_H
#define GRA_SPACE_INVADERS_SCREENMANAGERREMOTECONTROL_H

#include <string>
#include <vector>
#include "GameObject.h"
#include "GameObjectSharer.h"

class ScreenManagerRemoteControl
{
public:
    virtual void SwitchScreens(std::string screenTOSwitchTO) = 0;
    virtual void loadLevelInPlayMode(std::string screenToLoad) = 0;
    virtual std::vector<GameObject>& getGameObjects() = 0;
    virtual GameObjectSharer& shareGameObjectSharer() = 0;
};

#endif //GRA_SPACE_INVADERS_SCREENMANAGERREMOTECONTROL_H
