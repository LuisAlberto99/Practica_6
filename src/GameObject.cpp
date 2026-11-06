#include "GameObject.hpp"

void GameObject::Update(float dt)
{
    if (!m_active) return;
    for (auto &component : m_components)
    {
        component->Update(dt);
    }
}

void GameObject::FixedUpdate(float fixed_dt)
{
    if (!m_active) return;
    for (auto &component : m_components)
    {
        component->FixedUpdate(fixed_dt);
    }
}

void GameObject::Render(SDL_Renderer *renderer)
{
    if (!m_active) return;
    for (auto &component : m_components)
    {
        component->Render(renderer);
    }
}

void GameObject::OnCollision(GameObject *other)
{
    if (!m_active) return;
    for (auto &component : m_components)
    {
        component->OnCollision(other);
    } 
}