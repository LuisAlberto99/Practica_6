#pragma once

#include <vector>
#include "Scene.hpp"

class ResourceManager;
class SpriteComponent;
class TransformComponent;

class ResourceDemoScene : public Scene
{
    public:
        ResourceDemoScene(SceneManager *manager, ResourceManager *resources);
        ~ResourceDemoScene();

        void Init() override;
        void Update(float dt) override;
        void Render(SDL_Renderer *renderer) override;
        void HandleEvent(const SDL_Event &event) override;

    private:
        struct Enemy
        {
            TransformComponent *transform;
            SpriteComponent *sprite;
            float baseX;
            float phase;
        };

    void SpawnEnemies(int count);
    void ReloadTextures();
    void PrintMetrics() const;
    void TriggerDeliberateLeak();

    ResourceManager *m_resources;
    TransformComponent *m_playerTransform{nullptr};
    SpriteComponent *m_backgroundSprite{nullptr};
    SpriteComponent *m_playerSprite{nullptr};
    std::vector<Enemy> m_enemies;
    float m_time{0.0f};
};