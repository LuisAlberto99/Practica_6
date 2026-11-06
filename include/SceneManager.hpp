#pragma once

#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include "Scene.hpp"

enum class SceneAction
{
    None,
    Change,
    Push,
    Pop,
    Clear
};

class SceneManager
{
    private:
        std::vector<std::unique_ptr<Scene>> m_scenes;
        SceneAction m_pendingAction{SceneAction::None};
        std::unique_ptr<Scene> m_pendingScene{nullptr};

    public:
        SceneManager() = default;

        void ChangeScene(std::unique_ptr<Scene> new_scene)
        {
            m_pendingAction = SceneAction::Change;
            m_pendingScene = std::move(new_scene);
        }

        void PushScene(std::unique_ptr<Scene> new_scene)
        {
            m_pendingAction = SceneAction::Push;
            m_pendingScene = std::move(new_scene);
        }

        void PopScene()
        {
            m_pendingAction = SceneAction::Pop;
        }

        void Clear()
        {
            m_pendingAction = SceneAction::Clear;
        }

        bool HasScenes() const
        {
            return !m_scenes.empty();
        }

        void ProcessPendingChanges();
        void HandleEvent(const SDL_Event &event);
        void Update(float dt);
        void FixedUpdate(float fixed_dt);
        void Render(SDL_Renderer *renderer);
};