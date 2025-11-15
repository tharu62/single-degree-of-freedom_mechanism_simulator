#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "raylib.h"
#include "vector.h"
#include "body.h"
#include "draw.h"

Color RandomColor();
void init_camera(Camera2D* Camera);
void init_bodies(rigid_body* body_list, int body_count);
void input_camera(Camera2D* camera);
void window(Camera2D* camera);
void draw_margins();
void draw_legend();

void PhysicsEngineRun();

#endif // APPLICATION_H