#include "RenderGame.hpp"
#include "Globals.hpp"
#include "Nodes.hpp"
#include "raylib.h"
#include "env.hpp"
#include "LoadTextures.hpp"
#include <string>
#include <iostream>

void renderGame() {
    screenHeight = GetScreenHeight();
    screenWidth = GetScreenWidth();

    // Get node info
    nodeInfo a = nodesInfo[currentNodeID];
    Texture2D tex = Textures[a.FrameTextureID];

    BeginDrawing();
    ClearBackground((Color) {54, 54, 54, 255});

    BeginMode2D(cc);
    drawEnv();

    //renders the nodes
    for (auto& node : nodes) {
        node->draw();
    }

    DrawTexture(Textures[10], griddedMouseWorld.x, griddedMouseWorld.y, WHITE);

    EndMode2D();

    //User interface
    DrawText("CircuitBorn - v0.0.1", 0, 0, 20, (Color){255,255,255,150});
    std::string nodeCountText = "Nodes - " + std::to_string(nodes.size());
    DrawText(nodeCountText.c_str(), 0, 20, 20, (Color){255,255,255,150});
    DrawText("P - Power/Pause all entry nodes.", 0, 40, 20, (Color){255,255,255,150});
    DrawText("D - Delete", 0, 60, 20, (Color){255,255,255,150});

    float rectWidth  = screenWidth * 0.08f;   // 8% of screen width
    float rectHeight = screenHeight * 0.08f;  // 8% of screen height
    float rectX = screenWidth - rectWidth - screenWidth * 0.02f; // 2% margin from right
    float rectY = screenHeight * 0.02f;       // 2% margin from top

    // Scale texture slightly bigger than rectangle (e.g., 1.2x)
    float texScaleX = rectWidth / tex.width * 1.0f;
    float texScaleY = rectHeight / tex.height * 1.0f;

    // Compute texture position to center it
    float texX = rectX + rectWidth/2 - (tex.width * texScaleX)/2;
    float texY = rectY + rectHeight/2 - (tex.height * texScaleY)/2;

    // Draw semi-transparent rectangle
    //DrawRectangle(rectX, rectY, rectWidth / tex.width, rectHeight / tex.height, (Color){255, 255, 255, 150});

    const char* label = a.Name.c_str();
    const char* desc  = a.Desc.c_str();

    int fontSize = screenHeight * 0.03f; // 3% of screen height
    int descFontSize = screenHeight * 0.02f; // smaller font for description


    int textWidth = MeasureText(label, fontSize);

    float textX = rectX - textWidth - screenWidth * 0.01f; // 1% screen width margin
    float textY = rectY + rectHeight/2 - fontSize;         // top-aligned relative to rectangle center

    // Draw node name
    DrawText(label, (int)textX, (int)textY, fontSize, WHITE);

    // Draw node description under the name
    float descX = rectX - MeasureText(desc, descFontSize) - screenWidth * 0.01f; // left align like name
    float descY = textY + fontSize + screenHeight * 0.005f; // small vertical spacing
    DrawText(desc, (int)descX, (int)descY, descFontSize, WHITE);

    
    // Draw texture
    DrawTextureEx(tex, (Vector2){texX, texY}, 0.0f, texScaleX, WHITE);
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