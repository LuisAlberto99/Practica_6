#include "Scene.hpp"

void Scene::Update(float dt)
{
    for (auto &entity : m_entities)
    {
        entity->Update(dt);
    }
}

void Scene::FixedUpdate(float fixed_dt)
{
    for (auto &entity : m_entities)
    {
        entity->FixedUpdate(fixed_dt);
    }
}

void Scene::Render(SDL_Renderer *renderer)
{
    for (auto &entity : m_entities)
    {
        entity->Render(renderer);
    }
}

GameObject *Scene::CreateGameObjects(std::string tag)
{
    auto obj = std::make_unique<GameObject>(std::move(tag));
    GameObject *ptr = obj.get();
    m_entities.push_back(std::move(obj));
    return ptr;
}