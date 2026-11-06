#pragma once

#include <vector>
#include <memory>
#include <SDL3/SDL.h>

class GameObject;
class ColliderComponent;

class CollisionManager
{
private:
    std::vector<std::unique_ptr<GameObject>> *m_entities;

public:
    explicit CollisionManager(std::vector<std::unique_ptr<GameObject>> *entities)
        : m_entities{entities} {}

    bool CheckAABB(const SDL_FRect &a, const SDL_FRect &b) const;
    bool CheckCollision(const ColliderComponent &a, const ColliderComponent &b) const;
    void CheckCollisions();
};