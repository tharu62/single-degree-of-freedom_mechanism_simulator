#include "draw.h"

void draw(Camera2D* camera, rigid_body* body_list, int body_count) {

    for (int i = 0; i < body_count; ++i) {
        switch (body_list[i].shape)
        {
        case Circle:
            DrawCircleV(body_list[i].position, body_list[i].radius, body_list[i].color);
            break;

        case Box:
            DrawRectangleV(body_list[i].position, (vec){body_list[i].width, body_list[i].height}, body_list[i].color);
            break;

        default:
            break;
        }
    }
}