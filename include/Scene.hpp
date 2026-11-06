#pragma once

#include <vector>
#include <memory>
#include <string>
#include <SDL3/SDL.h>
#include "GameObject.hpp"

class SceneManager;

class Scene
{
protected:
    SceneManager *m_manager{nullptr};
    std::vector<std::unique_ptr<GameObject>> m_entities;
    std::string m_name;

public:
    Scene(SceneManager *m_manager, std::string name)
        : m_manager(m_manager), m_name(std::move(name)) {}

    virtual ~Scene() = default;

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;
    Scene(Scene &&) noexcept = default;
    Scene &operator=(Scene &&) noexcept = default;

    virtual void Init() {}
    virtual void Exit() {}
    virtual void HandleEvent(const SDL_Event &event) {}

    virtual void Update(float dt);
    virtual void FixedUpdate(float fixed_dt);
    virtual void Render(SDL_Renderer *renderer);

    GameObject *CreateGameObjects(std::string tag);

    std::vector<std::unique_ptr<GameObject>> &GetEntities()
    {
        return m_entities;
    }
};