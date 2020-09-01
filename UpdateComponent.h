#pragma once

#include "Component.h"

class UpdateComponent : public Component
{
private:
    std::string m_Type = "update";
    bool m_Enabled = false;
public:
    virtual void update(float fps) = 0;
    std::string getType()
    {
        return m_Type;
    }
    void disableComponent()
    {
        m_Enabled = false;
    }
    void enableComponent()
    {
        m_Enabled = true;
    }
    bool enabled()
    {
        return m_Enabled;
    }
    void start(
            GameObjectSharer* gos, GameObject* self) {
    }
};
