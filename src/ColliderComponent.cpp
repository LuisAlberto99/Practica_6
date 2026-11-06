#include "ColliderComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"

SDL_FRect ColliderComponent::GetWorldBounds() const
{
    if (!owner)
    {
        return SDL_FRect{offset.x, offset.y, size.x, size.y};

    }
    TransformComponent *transform = owner->GetComponent<TransformComponent>();
    if (!transform)
    {
        return SDL_FRect{offset.x, offset.y, size.x, size.y};
    }
    float x = transform->position.x + offset.x;
    float y = transform->position.y + offset.y;
    float w = size.x * transform->scale.x;
    float h = size.y * transform->scale.y;
    return SDL_FRect{x, y, w, h};
}

void ColliderComponent::RenderDebug(SDL_Renderer *renderer)
{
    SDL_FRect bounds = GetWorldBounds();

    if (is_colliding)
    {
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
    }
    SDL_RenderRect(renderer, &bounds);
}