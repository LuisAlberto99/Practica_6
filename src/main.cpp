#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cstdio>
#include <memory>
#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include "ResourceDemoScene.hpp"
#include "GameConstants.hpp"

struct AppState
{
    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};
    Uint64 last_ticks{0};
    float fixed_accumulator{0.0f};
    SceneManager sceneManager;
    ResourceManager resources;
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init falló: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    auto *app = new AppState();
    if (!SDL_CreateWindowAndRenderer("Práctica 06: Gestión de Recursos",
                                     static_cast<int>(GameConstants::WindowWidth),
                                     static_cast<int>(GameConstants::WindowHeight),
                                     0, &app->window, &app->renderer))
    {
        SDL_Log("No se pudo crear la ventana: %s", SDL_GetError());
        delete app;
        return SDL_APP_FAILURE;
    }

    app->resources.SetRenderer(app->renderer);
    app->last_ticks = SDL_GetTicks();

    app->sceneManager.ChangeScene(std::make_unique<ResourceDemoScene>(&app->sceneManager, &app->resources));
    app->sceneManager.ProcessPendingChanges();

    *appstate = app;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *app = static_cast<AppState *>(appstate);

    Uint64 current_ticks = SDL_GetTicks();
    float delta_time = static_cast<float>(current_ticks - app->last_ticks) / 1000.0f;
    app->last_ticks = current_ticks;
    if (delta_time > 0.25f)
    {
        delta_time = 0.25f;
    }

    app->sceneManager.ProcessPendingChanges();

    app->fixed_accumulator += delta_time;
    while (app->fixed_accumulator >= GameConstants::FixedDeltaTime)
    {
        app->sceneManager.FixedUpdate(GameConstants::FixedDeltaTime);
        app->sceneManager.ProcessPendingChanges();
        app->fixed_accumulator -= GameConstants::FixedDeltaTime;
    }

    app->sceneManager.Update(delta_time);
    app->sceneManager.Render(app->renderer);
    SDL_RenderPresent(app->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    AppState *app = static_cast<AppState *>(appstate);

    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    if (app && app->sceneManager.HasScenes())
    {
        app->sceneManager.HandleEvent(*event);
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState *app = static_cast<AppState *>(appstate);
    std::printf("[Engine] Cerrando subsistemas...\n");
    if (app)
    {
        app->sceneManager.Clear();
        app->sceneManager.ProcessPendingChanges();   // 1. mueren las escenas y sus sprites (observadores)
        app->resources.Clear();                      // 2. se destruyen las texturas, ANTES del renderer
        SDL_DestroyRenderer(app->renderer);          // 3. recién ahora el renderer
        SDL_DestroyWindow(app->window);
        delete app;
    }
    SDL_Quit();
    std::printf("[Engine] Recursos liberados. Cierre completado.\n");
}
