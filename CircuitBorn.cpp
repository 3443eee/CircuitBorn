#include <iostream>
#include "raylib.h"
#include "RenderGame.hpp"
#include "UpdateGame.hpp"
#include "LoadTextures.hpp"

#include "raymath.h"
#include "Globals.hpp"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(800, 450, "CircuitBorn");
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