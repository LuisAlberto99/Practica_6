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
        return it->second.get();

    }

    if (!m_renderer)
    {
        std::printf("[ResourceManager] Error: renderer nulo\n");
        return nullptr;
    }

    SDL_Surface *surface = IMG_Load(filepath.c_str());
    if (!surface)
    {
        std::printf("[ResourceManager] Error: no se pudo cargar %s: %s\n", filepath.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    SDL_DestroySurface(surface);

    if (!texture)
    {
        std::printf("[ResourceManager] Error al crear la textura: %s\n", SDL_GetError());
        return nullptr;
    }

    m_textures[filepath] = TexturePtr(texture);

    float w = 0.0f, h = 0.0f;
    SDL_GetTextureSize(texture, &w, &h);
    std::printf("[ResourceManager] Textura cargada en VRAM: '%s' (%.0fx%.0f px)\n",
                filepath.c_str(), w, h);

    return texture;
}

bool ResourceManager::HasTexture(const std::string &filepath) const
{
    return m_textures.find(filepath) != m_textures.end();
}

bool ResourceManager::UnloadTexture(const std::string &filepath)
{
    return m_textures.erase(filepath) > 0;
}

void ResourceManager::Clear()
{
    std::printf("[ResourceManager] Limpiando caché (%zu texturas liberadas).\n", m_textures.size());
    m_textures.clear();
}
