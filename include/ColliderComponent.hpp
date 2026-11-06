#pragma once

#include <SDL3/SDL.h>
#include"Component.hpp"
#include "Vector2.hpp"

class ColliderComponent : public Component
{
    public:
    Vector2 offset{0.0f, 0.0f};
    Vector2 size{60.0f, 60.0f};
    bool is_trigger{false};
    bool is_colliding{false};

    ColliderComponent() = default;
    ColliderComponent(Vector2 sz, Vector2 off = Vector2{0.0f, 0.0f}, bool trigger = false)
        : offset(off), size(sz), is_trigger(trigger) {}
    
    SDL_FRect GetWorldBounds() const;
    void RenderDebug(SDL_Renderer *renderer);
};