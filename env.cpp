#include "env.hpp"
#include "Globals.hpp"
#include "LoadTextures.hpp"
#include "raylib.h"
#include "raymath.h"
#include <limits>

void updateEnv() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            dragging = true;
            dragStart = GetMousePosition();
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) dragging = false;

    if (dragging) {
        Vector2 mousePos = GetMousePosition();
        Vector2 delta = Vector2Subtract(dragStart, mousePos);
        cc.target = Vector2Add(cc.target, Vector2Scale(delta, 1.0f / cc.zoom));
        dragStart = mousePos;
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        cc.zoom += wheel * 0.05f;
        if (cc.zoom < std::numeric_limits<float>::epsilon()) cc.zoom = std::numeric_limits<float>::epsilon(); // prevent flipping
    }
}

void drawEnv() {
    // Draw tiled background
    Rectangle texturePart = { 0, 0, Textures[0].width, Textures[0].height };
    Rectangle screenArea = {
        cc.target.x - GetScreenWidth() / 2 / cc.zoom,
        cc.target.y - GetScreenHeight() / 2 / cc.zoom,
        GetScreenWidth() / cc.zoom,
        GetScreenHeight() / cc.zoom
    };

    // --- Perfect grid-aligned tiling ---
    float tileW = (float)Textures[0].width;
    float tileH = (float)Textures[0].height;

    // Calculate where the first tile should start (snap to tile grid)
    float startX = floorf(screenArea.x / tileW) * tileW;
    float startY = floorf(screenArea.y / tileH) * tileH;

    // Draw tiles covering the entire visible area
    for (float y = startY; y < screenArea.y + screenArea.height; y += tileH) {
        for (float x = startX; x < screenArea.x + screenArea.width; x += tileW) {
            DrawTexture(Textures[0], (int)x, (int)y, WHITE);
        }
    }

    float groundTop = 500; // world Y position of top of the ground
    float groundTileW = (float)Textures[1].width;
    float groundTileH = (float)Textures[1].height;

    // Horizontal range
    startX = floorf(screenArea.x / groundTileW) * groundTileW;
    float endX = screenArea.x + screenArea.width;

    // Vertical range (from groundTop down to bottom of visible screen)
    startY = floorf(groundTop / groundTileH) * groundTileH;
    float endY = screenArea.y + screenArea.height;

    for (float y = startY; y < endY; y += groundTileH) {
        for (float x = startX; x < endX; x += groundTileW) {
            DrawTexture(Textures[1], (int)x, (int)y, WHITE);
        }
    }
}
float togrid(float value, float gridSize)
{
    return roundf(value / gridSize) * gridSize;
}
