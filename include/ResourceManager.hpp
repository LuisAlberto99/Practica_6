#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

struct TextureDeleter
{
    void operator()(SDL_Texture *texture) const noexcept
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
        }
    }
};

using TexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter>;

class ResourceManager
{
    private:
        SDL_Renderer *m_renderer{nullptr};
        std::unordered_map<std::string, TexturePtr> m_textures;
    public:
        ResourceManager()=default;
        explicit ResourceManager(SDL_Renderer *renderer);
        ~ResourceManager();

        ResourceManager(const ResourceManager &) =delete;
        ResourceManager &operator=(const ResourceManager &) = delete;

        ResourceManager(ResourceManager &&) noexcept = default;
        ResourceManager &operator=(ResourceManager &&) noexcept = default;

        void SetRenderer(SDL_Renderer *renderer) {m_renderer = renderer;}
        SDL_Renderer *GetRenderer() const { return m_renderer; }

        SDL_Texture *GetTexture(const std::string &filepath);
        bool HasTexture(const std::string &filepath) const;
        size_t GetTextureCount() const { return m_textures.size(); }
        bool UnloadTexture(const std::string &filepath);
        void Clear();
};