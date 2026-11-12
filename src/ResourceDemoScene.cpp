#include "ResourceDemoScene.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include "SceneManager.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "ResourceManager.hpp"
#include "GameConstants.hpp"

namespace
{
    constexpr const char *kBackground = "assets/background.png";
    constexpr const char *kPlayer = "assets/player.png";
    constexpr const char *kEnemy = "assets/enemy.png";
    constexpr int kColumns = 10;
    constexpr float kPlayerSpeed = 300.0f;
}

ResourceDemoScene::ResourceDemoScene(SceneManager *manager, ResourceManager *resources)
    :Scene(manager,"ResourceDemo"), m_resources(resources)
{

}

ResourceDemoScene::~ResourceDemoScene()
{
    std::printf("[ResourceDemoScene]Saliendo de escena.\n");
}

void ResourceDemoScene::Init()
{
    GameObject *bg = CreateGameObjects("Background");
    bg->AddComponent<TransformComponent>(Vector2{0.0f,0.0f});
    m_backgroundSprite = bg->AddComponent<SpriteComponent>(
        m_resources->GetTexture(kBackground), GameConstants::WindowWidth, GameConstants::WindowHeight);
    
    GameObject *player =CreateGameObjects("Player");
    m_playerTransform = player->AddComponent<TransformComponent>(
        Vector2{GameConstants::WindowWidth * 0.5f - 24.0f, GameConstants::WindowHeight - 100.0f},
        Vector2{1.5f, 1.5f});
    m_playerSprite = player->AddComponent<SpriteComponent>(m_resources->GetTexture(kPlayer), 32.0f, 32.0f);

    SpawnEnemies(50);

    std::printf("[ResourceDemoScene] Escena iniciada con éxito.\n");
    PrintMetrics();
}

void ResourceDemoScene::SpawnEnemies(int count)
{
    static const SpriteColor tints[] = {
        {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.4f, 0.4f, 1.0f}, {1.0f, 1.0f, 0.4f, 1.0f},
        {0.5f, 0.8f, 1.0f, 1.0f}, {0.7f, 1.0f, 0.7f, 1.0f}
    };

    for (int i = 0; i < count; ++i)
    {
        int n = static_cast<int>(m_enemies.size());
        int col = n % kColumns;
        int row = n / kColumns;
        float x = 120.0f + col * 68.0f;
        float y = 40.0f + 44.0f * (row % 8);
        const SpriteColor &t =tints[row % 5];

        GameObject *enemy = CreateGameObjects("Enemy");
        auto *transform = enemy->AddComponent<TransformComponent>(Vector2{x, y});
        auto *sprite = enemy->AddComponent<SpriteComponent>(m_resources->GetTexture(kEnemy), 32.0f, 32.0f);
        sprite->SetColorMod(t.r, t.g, t.b, t.a);
        m_enemies.push_back({transform, sprite, x, col * 0.5f + row});
    }
}

void ResourceDemoScene::Update(float dt)
{
    Scene::Update(dt);
    m_time += dt;

    const bool *keys = SDL_GetKeyboardState(nullptr);
    Vector2 dir{0.0f, 0.0f};
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])  dir.x -= 1.0f;
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) dir.x += 1.0f;
    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])    dir.y -= 1.0f;
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])  dir.y += 1.0f;

    m_playerTransform->Translate(dir * (kPlayerSpeed * dt));
    m_playerTransform->position.x = std::clamp(m_playerTransform->position.x, 0.0f, GameConstants::WindowWidth - 48.0f);
    m_playerTransform->position.y = std::clamp(m_playerTransform->position.y, 0.0f, GameConstants::WindowHeight - 48.0f);

    for (auto &e : m_enemies)
    {
        e.transform->position.x = e.baseX + 30.0f * std::sin(m_time * 2.0f + e.phase);
    }
}

void ResourceDemoScene::Render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    Scene::Render(renderer);  
}

void ResourceDemoScene::HandleEvent(const SDL_Event &event)
{
    if (event.type != SDL_EVENT_KEY_DOWN)
    {
        return;
    }

    switch (event.key.scancode)
    {
    case SDL_SCANCODE_SPACE:
        SpawnEnemies(8);
        PrintMetrics();
        break;
    case SDL_SCANCODE_C:
        m_resources->Clear();
        ReloadTextures();      // los sprites apuntaban a texturas ya destruidas
        PrintMetrics();
        break;
    case SDL_SCANCODE_L:
        TriggerDeliberateLeak();
        break;
    case SDL_SCANCODE_ESCAPE:
    {
        SDL_Event quit{};
        quit.type = SDL_EVENT_QUIT;
        SDL_PushEvent(&quit);
        break;
    }
    default:
        break;
    }
}

void ResourceDemoScene::ReloadTextures()
{
    m_backgroundSprite->SetTexture(m_resources->GetTexture(kBackground));
    m_playerSprite->SetTexture(m_resources->GetTexture(kPlayer));
    for (auto &e : m_enemies)
    {
        e.sprite->SetTexture(m_resources->GetTexture(kEnemy));
    }
}

void ResourceDemoScene::PrintMetrics() const

{
    std::printf("======================================================================\n");
    std::printf("[Flyweight Metric] Entidades en escena : %zu\n", m_entities.size());
    std::printf("[Flyweight Metric] Texturas en VRAM    : %zu (esperado: 3)\n", m_resources->GetTextureCount());
    std::printf("======================================================================\n");
}

void ResourceDemoScene::TriggerDeliberateLeak()
{
    // FALLA DELIBERADA: se omite SDL_DestroySurface para que ASan reporte la fuga.
    for (int i = 0; i < 50; ++i)
    {
        SDL_Surface *surface = IMG_Load(kEnemy);
        (void)surface;
    }
    std::printf("[ResourceDemoScene] Se cargaron 50 superficies con IMG_Load() sin llamar a SDL_DestroySurface().\n");
}