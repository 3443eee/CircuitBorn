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

    //std::cout << "Screen: " << mouseScreen.x << "," << mouseScreen.y << std::endl;
    //std::cout << "World: " << mouseWorld.x << "," << mouseWorld.y << std::endl;

    for (auto& node : nodes) {
        node->update();  // propagate signals
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        switch (currentNodeID) {
        case 1:
            placeNode<EntryNode>({griddedMouseWorld.x, griddedMouseWorld.y});
            break;
        case 2:
            placeNode<WireNode>({griddedMouseWorld.x, griddedMouseWorld.y});
            break;
        case 3:
            placeNode<LampNode>({griddedMouseWorld.x, griddedMouseWorld.y});
        }
        
    }
    if (IsKeyPressed(KEY_P)) {
        running = !running;
    }
    // Assuming currentNodeID starts at 1
    if (IsKeyPressed(KEY_E)) {
        if (currentNodeID < (int)nodesInfo.size()) {
            currentNodeID += 1; 
        } else {
            currentNodeID = 1; // wrap around
        }
    }

    if (IsKeyPressed(KEY_Q)) {
        if (currentNodeID > 1) {
            currentNodeID -= 1;
        } else {
            currentNodeID = nodesInfo.size(); // wrap around
        }
    }

    if (IsKeyPressed(KEY_D)) {
        deleteNodeAt((Vector2) {griddedMouseWorld.x, griddedMouseWorld.y});
    }
}