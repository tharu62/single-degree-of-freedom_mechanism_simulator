#ifndef DRAWALL_H
#define DRAWALL_H

#include "raylib.h"
#include "body.h"

extern int screenWidth;
extern int screenHeight;

void draw(Camera2D* camera, rigid_body* body_list, int body_count);


#endif // DRAWALL_H