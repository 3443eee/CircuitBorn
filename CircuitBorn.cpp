#include <iostream>
#include "raylib.h"
#include "RenderGame.hpp"
#include "UpdateGame.hpp"
#include "LoadTextures.hpp"
#include "raymath.h"
#include "Globals.hpp"

int main() {
    // Set fullscreen mode and MSAA
    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_MSAA_4X_HINT);

    // Initialize window (size is ignored in fullscreen)
    InitWindow(0, 0, "CircuitBorn");

    SetTargetFPS(60);
    LoadAllSprites();
    initCamera();

    while (!WindowShouldClose()) {
        updateGame();
        renderGame();
    }

    UnloadAllTextures();
    CloseWindow();
    return 0;
}