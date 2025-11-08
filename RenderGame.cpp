#include "RenderGame.hpp"
#include "Globals.hpp"
#include "Nodes.hpp"
#include "raylib.h"
#include "env.hpp"
#include <string>

void renderGame() {
    BeginDrawing();
    ClearBackground(DARKPURPLE);
    
    BeginMode2D(cc);
    drawEnv();
    DrawRectangle(griddedMouseWorld.x, griddedMouseWorld.y, 16, 16, (Color) {255,255,255,100});

    //renders the nodes
    for (auto& node : nodes) {
        node->draw();
    }

    EndMode2D();

    //User interface
    DrawText("CircuitBorn - v0.0.1", 0, 0, 20, (Color){255,255,255,150});
    std::string nodeCountText = "Nodes - " + std::to_string(nodes.size());
    DrawText(nodeCountText.c_str(), 0, 20, 20, (Color){255,255,255,150});
    DrawText("P - Power/Pause all entry nodes.", 0, 40, 20, (Color){255,255,255,150});

    EndDrawing(); 
}

void initCamera() {
    dragging = false;
    dragStart = {0, 0};
    cc.target = (Vector2){ 0, 450 };
    cc.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    cc.rotation = 0.0f;
    cc.zoom = 2.0f;
}