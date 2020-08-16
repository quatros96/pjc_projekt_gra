//
// Created by quatr on 27.04.2020.
//

#ifndef GRA_SPACE_INVADERS_GAMEOBJECTBLUEPRINT_H
#define GRA_SPACE_INVADERS_GAMEOBJECTBLUEPRINT_H

#include <vector>
#include <string>
#include <map>

class GameObjectBlueprint
{
private:
    std::string m_Name = "";
    std::vector<std::string> m_ComponentList;
    std::string m_BitmapName = "";

    float m_Width;
    float m_Height;
    float m_LocationX;
    float m_LocationY;
    float m_Speed;
    bool m_EncompassingRectCollider {false};
    std::string m_EncompassingRectColliderLabel {""};
public:
    float getSpeed();
    void setSpeed(float speed);
    float getWidth();
    void setWidth(float width);
    float getHeight();
    void setHeight(float height);
    float getLacationX();
    void setLocationX(float locationX);
    float getLocationY();
    void setLocationY(float locationY);
    void setName(std::string name);
    std::string getName();
    std::vector<std::string>& getComponentList();
    void addToComponentList(std::string newComponent);
    std::string getBitmapName();
    void setBitmapName(std::string bitmapName);
    std::string getEncompassingRectColliderLabel();
    bool getEncompassingRectCollider();
    void setEncompassingRectCollider(std::string label);
};

#endif //GRA_SPACE_INVADERS_GAMEOBJECTBLUEPRINT_H
