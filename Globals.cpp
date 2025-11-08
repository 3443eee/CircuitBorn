#include "Globals.hpp"

Texture2D bg;
Texture2D ground;
Camera2D cc;
bool dragging;
Vector2 dragStart;
Vector2 mouseScreen;
Vector2 mouseWorld;
Vector2 griddedMouseWorld;
bool running;
int uiState;
int screenWidth;
int screenHeight;
int currentNodeID = 1;
int mode = 1;