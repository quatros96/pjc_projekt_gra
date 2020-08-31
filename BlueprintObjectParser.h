#pragma once

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
