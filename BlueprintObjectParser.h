//
// Created by quatr on 27.04.2020.
//

#ifndef GRA_SPACE_INVADERS_BLUEPRINTOBJECTPARSER_H
#define GRA_SPACE_INVADERS_BLUEPRINTOBJECTPARSER_H

#include "GameObjectBlueprint.h"
#include <string>

class BlueprintObjectParser
{
private:
    std::string extractStringBetweenTags(std::string stringToSearch,
            std::string startTag, std::string endTag);
public:
    void parseNextObjectForBlueprint(std::ifstream& reader, GameObjectBlueprint& bp);
};

#endif //GRA_SPACE_INVADERS_BLUEPRINTOBJECTPARSER_H
