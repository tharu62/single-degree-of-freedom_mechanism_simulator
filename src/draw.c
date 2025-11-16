#include "draw.h"

void draw(Camera2D* camera, rigid_body* body_list, int body_count) {

    for (int i = 0; i < body_count; ++i) {
        switch (body_list[i].shape)
        {
        case Circle:
            DrawCircleV(body_list[i].position, body_list[i].radius, body_list[i].color);
            break;

        case Box:
            Rectangle rec = {
                body_list[i].position.x + body_list[i].transformed_vertices[0].x,
                body_list[i].position.y + body_list[i].transformed_vertices[0].y,
                body_list[i].width,
                body_list[i].height
            };
            Vector2 origin = { body_list[i].width/2.f, body_list[i].height/2.f };

            DrawRectanglePro(rec, origin, body_list[i].rotation * RAD2DEG, body_list[i].color);
            break;

        default:
            break;
        }
    }
}