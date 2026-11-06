#include "CollisionManager.hpp"
#include "GameObject.hpp"
#include "ColliderComponent.hpp"

bool CollisionManager::CheckAABB(const SDL_FRect &a, const SDL_FRect &b) const //verificar si dos cajas se tocan
{
    return (a.x < b.x + b.w) &&
           (a.x + a.w > b.x) &&
           (a.y < b.y + b.h) &&
           (a.y + a.h > b.y);
}

bool CollisionManager::CheckCollision(const ColliderComponent &a, const ColliderComponent &b) const
{
    SDL_FRect bounds_a = a.GetWorldBounds();
    SDL_FRect bounds_b = b.GetWorldBounds();
    return CheckAABB(bounds_a, bounds_b);
}

void CollisionManager::CheckCollisions()
{
    if (!m_entities) return;

    size_t N = m_entities->size();

    // Limpieza de banderas
    for (auto &entity : *m_entities)
    {
        if (auto *col = entity->GetComponent<ColliderComponent>())
        {
            col->is_colliding = false;
        }
    }

    // Iteración
    for (size_t i = 0; i < N; ++i)
    {
        auto *colA = (*m_entities)[i]->GetComponent<ColliderComponent>();
        if (!colA) continue;

        for (size_t j = i + 1; j < N; ++j)
        {
            auto *colB = (*m_entities)[j]->GetComponent<ColliderComponent>();
            if (!colB) continue;

            if (CheckCollision(*colA, *colB))
            {
                colA->is_colliding = true;
                colB->is_colliding = true;

                (*m_entities)[i]->OnCollision((*m_entities)[j].get());
                (*m_entities)[j]->OnCollision((*m_entities)[i].get());
            }
        }
    }
}