#pragma once

#include <SDL3/SDL.h>
#include "Component.hpp"

struct SpriteColor
{
    float r{1.0f}, g{1.0f}, b{1.0f}, a{1.0f};
};

class SpriteComponent : public Component
{
    private:
        SDL_Texture *m_texture{nullptr};
        float m_width{0.0f};
        float m_height{0.0f};
        SDL_FRect m_srcRect{0.0f, 0.0f, 0.0f, 0.0f};
        bool m_useSrcRect{false};
        SpriteColor m_colorMod;
        SDL_FlipMode m_flip{SDL_FLIP_NONE};

    public:
    SpriteComponent() = default;
    SpriteComponent(SDL_Texture *texture, float width, float height)
        : m_texture(texture), m_width(width), m_height(height) {}
    
        void SetTexture(SDL_Texture *texture) {m_texture = texture; }
        void SetSize(float width, float height) {m_width = width; m_height = height; }
        void SetColorMod(float r, float g, float b, float a = 1.0f) { m_colorMod = {r, g, b, a}; }
    void SetFlip(SDL_FlipMode flip) { m_flip = flip; }

    void Render(SDL_Renderer *renderer) override;
};