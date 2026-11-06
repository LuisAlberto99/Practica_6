#include "ResourceManager.hpp"
#include <cstdio>

ResourceManager::ResourceManager(SDL_Renderer *renderer) : m_renderer(renderer) {}

ResourceManager::~ResourceManager()
{
    Clear();
}

SDL_Texture *ResourceManager::GetTexture(const std::string &filepath)
{
    auto it =m_textures.find(filepath);
    if (it != m_textures.end())
    {
        return /* ??? */;

    }

    if (!m_renderer)
    {
        std::printf("[ResourceManager] Error: renderer nulo\n");
        return nullptr;
    }
}
