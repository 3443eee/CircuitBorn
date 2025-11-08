#include "Nodes.hpp"
#include <vector>
#include <memory>
#include <map>

std::vector<std::unique_ptr<Node>> nodes;
std::map<Vector2, Node*, Vector2Compare> nodesPosMap;

std::vector<Node*> getNeighbors(Node* n) {
    std::vector<Node*> nearby;

    Vector2 offsets[] = {
        {16, 0}, {-16, 0}, {0, 16}, {0, -16} // 4 directions
    };

    for (Vector2 offset : offsets) {
        Vector2 neighborPos = {n->pos.x + offset.x, n->pos.y + offset.y};
        auto it = nodesPosMap.find(neighborPos);
        if (it != nodesPosMap.end()) {
            nearby.push_back(it->second);
        }
    }
    return nearby;
}

void updateWireOrientation(WireNode* wire) {
    // Check neighbors
    bool up = false, down = false, left = false, right = false;

    Vector2 offsets[] = { {0,-16}, {0,16}, {-16,0}, {16,0} }; // up, down, left, right
    for (Vector2 offset : offsets) {
        Vector2 neighborPos = { wire->pos.x + offset.x, wire->pos.y + offset.y };
        auto it = nodesPosMap.find(neighborPos);
        if (it == nodesPosMap.end()) continue;

        WireNode* w = dynamic_cast<WireNode*>(it->second);
        if (!w) continue;

        if (offset.x == 0 && offset.y == -16) up = true;
        if (offset.x == 0 && offset.y == 16) down = true;
        if (offset.x == -16 && offset.y == 0) left = true;
        if (offset.x == 16 && offset.y == 0) right = true;
    }

    // Determine type & rotation
    int connections = up + down + left + right;

    if (connections == 4) {
        wire->texture = Textures[9]; // cross
        wire->rotation = 0;
        wire->type = 4;
    } else if (connections == 3) {
        wire->texture = Textures[8]; // T-junction
        wire->type = 3;
        // Rotate so missing direction is on top
        if (!up) wire->rotation = 0;
        else if (!right) wire->rotation = 90;
        else if (!down) wire->rotation = 180;
        else if (!left) wire->rotation = 270;
    } else if (connections == 2) {
        if ((up && down) || (left && right)) {
            wire->texture = Textures[6]; // straight
            wire->type = 2;
            wire->rotation = (left && right) ? 90 : 0;
        } else {
            wire->texture = Textures[7]; // corner
            wire->type = 2;
            if (down && right) wire->rotation = 0;
            else if (down && left) wire->rotation = 90;
            else if (up && left) wire->rotation = 180;
            else if (up && right) wire->rotation = 270;
        }
    } else if (connections == 1) {
        wire->texture = Textures[6]; // single wire
        wire->type = 1;
        if (up || down) wire->rotation = 0;
        else wire->rotation = 90;
    } else {
        wire->texture = Textures[6]; // default
        wire->type = 1;
        wire->rotation = 0;
    }
}