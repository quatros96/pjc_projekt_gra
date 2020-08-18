//
// Created by quatr on 27.04.2020.
//

#include "BlueprintObjectParser.h"
#include "ObjectTags.h"
#include <iostream>
#include <fstream>

void BlueprintObjectParser::parseNextObjectForBlueprint(std::ifstream &reader, GameObjectBlueprint &bp)
{
    std::string lineFromFile;
    std::string value {};
    while(std::getline(reader, lineFromFile))
    {
        if(lineFromFile.find(ObjectTags::COMPONENT) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                    ObjectTags::COMPONENT, ObjectTags::COMPONENT_END);
            bp.addToComponentList(value);
        }
        else if(lineFromFile.find(ObjectTags::NAME) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                    ObjectTags::NAME, ObjectTags::NAME_END);
            bp.setName(value);
        }
        else if(lineFromFile.find(ObjectTags::WIDTH) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                    ObjectTags::WIDTH, ObjectTags::WIDTH_END);
            bp.setWidth(stof(value));
        }
        else if(lineFromFile.find(ObjectTags::HEIGHT) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                    ObjectTags::HEIGHT, ObjectTags::HEIGHT_END);
            bp.setHeight(stof(value));
        }
        else if(lineFromFile.find(ObjectTags::LOCATION_X) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                    ObjectTags::LOCATION_X, ObjectTags::LOCATION_X_END);
            bp.setLocationX(stof(value));
        }
        else if(lineFromFile.find(ObjectTags::LOCATION_Y) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                    ObjectTags::LOCATION_Y, ObjectTags::LOCATION_Y_END);
            bp.setLocationY(stof(value));
        }
        else if(lineFromFile.find(ObjectTags::BITMAP_NAME) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                    ObjectTags::BITMAP_NAME, ObjectTags::BITMAP_NAME_END);
            bp.setBitmapName(value);
        }
        else if(lineFromFile.find(ObjectTags::ENCOMPASSING_RECT_COLLIDER) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                    ObjectTags::ENCOMPASSING_RECT_COLLIDER, ObjectTags::ENCOMPASSING_RECT_COLLIDER_END);
            bp.setEncompassingRectCollider(value);
        }
        else if (lineFromFile.find(ObjectTags::SPEED) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                ObjectTags::SPEED, ObjectTags::SPEED_END);
            bp.setSpeed(stof(value));
        }

        else if (lineFromFile.find(ObjectTags::WIDTH_OFFSET) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                ObjectTags::WIDTH_OFFSET, ObjectTags::WIDTH_OFFSET_END);
            bp.setWidthOffset(stof(value));
        }
        else if (lineFromFile.find(ObjectTags::HEIGHT_OFFSET) != std::string::npos)
        {
            value = extractStringBetweenTags(lineFromFile,
                ObjectTags::HEIGHT_OFFSET, ObjectTags::HEIGHT_OFFSET_END);
            bp.setHeightOffset(stof(value));
        }
    	
        else if(lineFromFile.find(ObjectTags::END_OF_OBJECT) != std::string::npos)
        {
            return;
        }
    }
}
std::string BlueprintObjectParser::extractStringBetweenTags(std::string stringToSearch, std::string startTag, std::string endTag)
{
    int start = startTag.length();
    int count = stringToSearch.length() - startTag.length() - endTag.length();
    std::string stringBetweenTags = stringToSearch.substr(start, count);
    return stringBetweenTags;
}