#ifndef NODES_HPP
#define NODES_HPP

#include "raylib.h"
#include "raymath.h"
#include "LoadTextures.hpp"
#include "Globals.hpp"
#include <vector>
#include <string>
#include <memory> 
#include <map>
#include <unordered_map>
#include <algorithm>

class Node {
public:
    Vector2 pos;
    bool powered = false;
    bool powers = false;
    int nodeID;

    Node(Vector2 p) : pos(p) {}
    virtual ~Node() = default;

    virtual void update() {}        // default does nothing
    virtual void draw() {}  // must implement in derived classes
};

struct Vector2Compare {
    bool operator()(const Vector2& a, const Vector2& b) const {
        if (a.x == b.x)
            return a.y < b.y;
        return a.x < b.x;
    }
};

extern std::vector<std::unique_ptr<Node>> nodes;
extern std::map<Vector2, Node*, Vector2Compare> nodesPosMap;

inline Vector2 offsets[] = {
    {16, 0}, {-16, 0}, {0, 16}, {0, -16}
};

std::vector<Node*> getNeighbors(Node* n);

class EntryNode : public Node {
public:
    Texture2D texture;

    EntryNode(Vector2 p)
        : Node(p), texture(Textures[2]) {
            nodeID = 1;
            powers = true;
        }

    void update() override {
        if (running) {
            powered = true;
            texture = Textures[3];
        } else {
            powered = false;
            texture = Textures[2];
        }
    }

    void draw() override {
        DrawTexture(texture, (int)pos.x, (int)pos.y, WHITE);
    }
};

class WireNode : public Node {
public:
    Texture2D texture;
    int type;
    Rectangle sourceRec;
    Rectangle destRec;
    Vector2 origin;
    float rotation;

    WireNode(Vector2 p) : Node(p) {
        powers = true;
        nodeID = 2;
        texture = Textures[6];
        type = 1;
        // Sample entire texture
        sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height};
        destRec = { pos.x + texture.width / 2.0f, pos.y + texture.height / 2.0f, (float)texture.width, (float)texture.height };
        origin = { texture.width / 2.0f, texture.height / 2.0f };
        rotation = 0;
    };

    void update() override {
        powered = false;
        if (!running) return;
        // Directions for 4-neighbor check (up, down, left, right)

        for (Vector2 offset : offsets) {
            Vector2 neighborPos = {pos.x + offset.x, pos.y + offset.y};

            // Check if neighbor exists in the map
            auto it = nodesPosMap.find(neighborPos);
            if (it != nodesPosMap.end()) {
                Node* neighbor = it->second;
                if (neighbor->powers && neighbor->powered) {
                    powered = true;
                }
            }
        }
    }

    void draw() override {
        if (powered) {
            DrawTexturePro(texture, sourceRec, destRec, origin, rotation, (Color) {180, 0, 0, 255});
        } else {
            DrawTexturePro(texture, sourceRec, destRec, origin, rotation, (Color) {173, 173, 173, 255});
        }
        
    }
};

class LampNode : public Node {
public:
    Texture2D texture;
    
    LampNode(Vector2 p) : Node(p) {
        nodeID = 3;
        texture = Textures[5];
    }

    void update() override {
        powered = false;
        texture = Textures[5];
        if (!running) return;
        
        for (Vector2 offset : offsets) {
            Vector2 neighborPos = {pos.x + offset.x, pos.y + offset.y};

            auto it = nodesPosMap.find(neighborPos);
            if (it != nodesPosMap.end()) {
                Node* neighbor = it->second;
                if (neighbor->powers && neighbor->powered) {
                    powered = true;
                    break;
                }
            }
        }

        if (powered) {
            texture = Textures[4];
        } else {
            texture = Textures[5];
        }
    }

    void draw() override {
        DrawTexture(texture, (int)pos.x, (int)pos.y, WHITE);
    }
};

void updateWireOrientation(WireNode* wire);

struct nodeInfo {
    std::string Name;
    std::string Desc;
    int FrameTextureID;
};

inline std::map<int, nodeInfo> nodesInfo = {
    {1, {"Entry node", "The start of everything...", 3}},
    {2, {"Wire", "Transfers power", 6}},
    {3, {"Lamp", "Lights up when powered", 5}}
};

template<typename T>
int placeNode(Vector2 pos) {
    if (nodesPosMap[pos]) return 1;

    auto node = std::make_unique<T>(pos);
    Node* rawNodePtr = node.get();
    nodes.push_back(std::move(node));
    nodesPosMap[pos] = rawNodePtr;

    // If it's a wire, update itself and neighbors
    if (rawNodePtr->nodeID == 2) {
        WireNode* wire = dynamic_cast<WireNode*>(rawNodePtr);
        if (wire) {
            updateWireOrientation(wire);
            auto neighbors = getNeighbors(wire);
            for (Node* n : neighbors) {
                WireNode* w = dynamic_cast<WireNode*>(n);
                if (w) updateWireOrientation(w);
            }
        }
    }

    return 0;
}

inline void deleteNodeAt(Vector2 pos) {
    auto it = nodesPosMap.find(pos);
    if (it == nodesPosMap.end()) return; 
    Node* nodePtr = it->second;

    auto vecIt = std::find_if(nodes.begin(), nodes.end(),
        [nodePtr](const std::unique_ptr<Node>& n) { return n.get() == nodePtr; });
    if (vecIt != nodes.end()) {
        nodes.erase(vecIt);
    }

    nodesPosMap.erase(it);
}

#endif