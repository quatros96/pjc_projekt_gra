#pragma once

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
    float m_WidthOffset;
    float m_HeightOffset;
    bool m_EncompassingRectCollider {false};
    std::string m_EncompassingRectColliderLabel {""};
    std::vector<std::string> m_Animations;
public:
    float getWidthOffset();
    void setWidthOffset(float widthoff);
    float getHeightOffset();
    void setHeightOffset(float widthoff);
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
    std::vector<std::string>& getAnimations();
};
