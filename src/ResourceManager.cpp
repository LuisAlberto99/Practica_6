#include "ResourceManager.hpp"
#include <cstdio>

ResourceManager::ResourceManager(SDL_Renderer *renderer) : m_renderer(renderer) {}

ResourceManager::~ResourceManager()
{
    Clear();
}