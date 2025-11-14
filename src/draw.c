#include "draw.h"

void draw(Rectangle* player, Camera2D* camera){

    DrawRectangleRec(*player, RED);
    DrawRectangle(-6000-screenWidth, 320, 13000+screenWidth, 8000, DARKGRAY);

    DrawLine((int)camera->target.x, -screenHeight*10, (int)camera->target.x, screenHeight*10, GREEN);
    DrawLine(-screenWidth*10, (int)camera->target.y, screenWidth*10, (int)camera->target.y, GREEN);

}