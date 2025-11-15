#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "vector.h"
#include "draw.h"

void init(Camera2D* Camera);
void input(Camera2D* camera);
void window(Camera2D* camera);
void draw_margins();
void draw_legend();

void PhysicsEngineRun();

#endif // APPLICATION_H