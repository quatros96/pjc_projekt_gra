//
// Created by quatr on 21.04.2020.
//

#include "BitmapStore.h"
#include <assert.h>
#include <iostream>

BitmapStore* BitmapStore::m_s_Instance {nullptr};
BitmapStore::BitmapStore()
{
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}
void BitmapStore::addBitmap(const std::string &filename)
{
    //get reference to m_textures using ms_instance
    auto& bitmapsMap = m_s_Instance->m_BitmapsMap;
    auto keyValuePair = bitmapsMap.find(filename);
    if(keyValuePair == bitmapsMap.end())
    {
        //create new key value
        auto& texture = bitmapsMap[filename];
        texture.loadFromFile(filename);
    }

}
sf::Texture& BitmapStore::getBitmap(const std::string &filename)
{
    auto& m = m_s_Instance->m_BitmapsMap;
    auto keyValuePair = m.find(filename);
    if(keyValuePair != m.end())
    {
        return keyValuePair->second;
    }
    else
    {
#ifdef debuggingOnConsole
        std::cout << "BitmapStore::getBitmap() Texture not found crash!" << std::endl;
#endif
        std::cout << "blad !!!! ";
        return keyValuePair->second;
    }
}