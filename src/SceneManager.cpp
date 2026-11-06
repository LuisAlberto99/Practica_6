#include "SceneManager.hpp"

void SceneManager::ProcessPendingChanges()
{
    if (m_pendingAction == SceneAction::None)
    {
        return;
    }
    switch (m_pendingAction)
    {
        case SceneAction::Change:
        {
            if (!m_scenes.empty())
            {
                m_scenes.back()->Exit();
                m_scenes.pop_back();
            }
            if (m_pendingScene)
            {
                m_scenes.push_back(std::move(m_pendingScene));
                m_scenes.back()->Init();
            }
            break;
        }
        case SceneAction::Push:
        {
            if (m_pendingScene)
            {
                m_scenes.push_back(std::move(m_pendingScene));
                m_scenes.back()->Init();
            }
            break;
        }
        case SceneAction::Pop:
        {
            if (!m_scenes.empty())
            {
                m_scenes.back()->Exit();
                m_scenes.pop_back();
            }
            break;
        }
        case SceneAction::Clear:
        {
            while (!m_scenes.empty())
            {
                m_scenes.back()->Exit();
                m_scenes.pop_back();
            }
            break;
        }
        default:
            break;
    }

    m_pendingAction = SceneAction::None;
    m_pendingScene.reset();
}

void SceneManager::HandleEvent(const SDL_Event &event)
{
    if (!m_scenes.empty())
    {
        m_scenes.back()->HandleEvent(event);
    }
}

void SceneManager::Update(float dt)
{
    if (!m_scenes.empty())
    {
        m_scenes.back()->Update(dt);
    }
}
void SceneManager::FixedUpdate(float fixed_dt)
{
    if (!m_scenes.empty())
    {
        m_scenes.back()->FixedUpdate(fixed_dt);
    }
}

void SceneManager::Render(SDL_Renderer *renderer)
{
    for (auto &scene : m_scenes)
    {
        scene->Render(renderer);
    }
}