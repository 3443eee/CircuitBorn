#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include "raylib.h"

extern Camera2D cc;
extern bool dragging;
extern Vector2 dragStart;
extern Vector2 mouseScreen;
extern Vector2 mouseWorld;
extern Vector2 griddedMouseWorld;
extern bool running;
extern int screenWidth;
extern int screenHeight;
extern int currentNodeID;
extern int mode;

#endif