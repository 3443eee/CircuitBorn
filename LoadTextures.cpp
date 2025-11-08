#include "LoadTextures.hpp"
#include "raylib.h"
#include "Globals.hpp"
#include <vector>

std::vector<Texture2D> Textures;

Texture2D LoadTextureFromFile(const char* filename) {
    Texture2D texture = LoadTexture(filename);
    //SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    Textures.push_back(texture);
    return texture;
}

void UnloadAllTextures() {
    for (auto& texture : Textures) {
        UnloadTexture(texture);
    }
    Textures.clear();
}

void registerTexture(Texture2D texture) {
    Textures.push_back(texture);
}

void LoadAllSprites() {
    LoadTextureFromFile("res/bg.png"); // 0
    LoadTextureFromFile("res/ground.png"); // 1
    LoadTextureFromFile("res/entry_off.png"); // 2
    LoadTextureFromFile("res/entry_on.png"); // 3
    LoadTextureFromFile("res/lamp_on.png"); // 4
    LoadTextureFromFile("res/lamp_off.png"); // 5
    LoadTextureFromFile("res/wire.png"); // 6
    LoadTextureFromFile("res/wire_turn.png"); // 7
    LoadTextureFromFile("res/wire_3.png"); // 8
    LoadTextureFromFile("res/wire_4.png"); // 9
    LoadTextureFromFile("res/hover.png"); // 10
}
