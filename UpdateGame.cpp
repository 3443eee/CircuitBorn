#include "UpdateGame.hpp"
#include "raylib.h"
#include "Globals.hpp"
#include "Nodes.hpp"
#include "env.hpp"
#include <iostream>

void updateGame() {
    updateEnv();
    mouseScreen = GetMousePosition();
    mouseWorld = GetScreenToWorld2D(mouseScreen, cc);
    griddedMouseWorld = (Vector2) {togrid((mouseWorld.x - 8), 16), togrid((mouseWorld.y - 8), 16)};

    std::cout << "Screen: " << mouseScreen.x << "," << mouseScreen.y << std::endl;
    std::cout << "World: " << mouseWorld.x << "," << mouseWorld.y << std::endl;

    for (auto& node : nodes) {
        node->update();  // propagate signals
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        placeNode<EntryNode>({griddedMouseWorld.x, griddedMouseWorld.y});
    }
    if (IsKeyPressed(KEY_P)) {
        running = !running;
    }
    if (IsKeyDown(KEY_O)) {
        placeNode<WireNode>({griddedMouseWorld.x, griddedMouseWorld.y});
    }
    if (IsKeyDown(KEY_L)) {
        placeNode<LampNode>({griddedMouseWorld.x, griddedMouseWorld.y});
    }
}