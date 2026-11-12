#pragma once

#include <SDL3/SDL.h>

namespace GameConstants
{
    inline constexpr float WindowWidth = 960.0f;
    inline constexpr float WindowHeight = 540.0f;

    inline constexpr float PaddleWidth = 20.0f;
    inline constexpr float PaddleHeight = 100.0f;
    inline constexpr float PaddleSpeed = 400.0f; //Velocidad de la paleta del jugador.
    constexpr SDL_Color PlayerColor{80, 200, 255, 255}; //Color de la paleta del jugador
    constexpr SDL_Color AIColor{255, 120, 80, 255}; //Color de la paleta de la IA
    constexpr SDL_Color BallColor{255, 255, 255, 255}; //Color de la pelota 
    inline constexpr float FixedDeltaTime = 1.0f / 60.0f; //diferencias en el tiempo

    inline constexpr float BallSize = 16.0f;
    inline constexpr float BallInitialSpeed = 400.0f; //Velocidad de inicio de la pelota.
    inline constexpr float BallMaxSpeed = 700.0f; //
    inline constexpr float BallSpeedUpFactor = 1.08f; // multiplicador de velocidad tras cada rebote en paleta
    inline constexpr float BallMaxBounceAngleDeg = 60.0f; // ángulo máximo de rebote respecto a la horizontal

    inline constexpr int WinningScore = 7; //Puntos para ganar

    inline constexpr float GoalSensorWidth = 20.0f; // ancho del sensor de anotación, fuera de cada borde
};