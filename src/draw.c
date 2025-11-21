#include "draw.h"
#include <stdlib.h>

void draw (Camera2D* camera, rigid_body* body_list, int body_count) {

    for (int i = 0; i < body_count; ++i) {
        switch (body_list[i].shape)
        {
        case Circle:
            DrawCircleV((vec){body_list[i].position.x,-body_list[i].position.y}, body_list[i].radius, body_list[i].color);
            break;

        case Box:
            vec p[4] = {
                body_list[i].transformed_vertices.array[0], // top-left
                body_list[i].transformed_vertices.array[1], // top-right
                body_list[i].transformed_vertices.array[2], // bottom-right
                body_list[i].transformed_vertices.array[3]  // bottom-left
            };
            for (int k = 0; k < 4; k++) {
                p[k].y = -p[k].y;
            }
            Color color = body_list[i].color;
            DrawLineV(p[0], p[1], color);
            DrawLineV(p[1], p[2], color);
            DrawLineV(p[2], p[3], color);
            DrawLineV(p[3], p[0], color);
            break;
        default:
            break;
        }
    }
    return;
}


 void draw_with_sat_detection (Camera2D* camera, rigid_body* body_list, int body_count) {
    // Precompute collision flags so both bodies in a colliding pair are drawn red
    bool* colliding = calloc((size_t)body_count, sizeof(bool));
    if (!colliding) return;

    vec v = {0.f, 0.f};
    float temp = 0.f;

    for (int i = 0; i < body_count; ++i) {
        for (int j = i + 1; j < body_count; ++j) {
            if (body_list[i].shape == Circle && body_list[j].shape == Circle) {
                if (circles_collide(&body_list[i], &body_list[j])) {
                    colliding[i] = colliding[j] = true;
                }
            } else if (body_list[i].shape == Box && body_list[j].shape == Box) {
                if (sat_polygons(&body_list[i].transformed_vertices, &body_list[j].transformed_vertices, &v, &temp)) {
                    colliding[i] = colliding[j] = true;
                }
            } else {
                // One circle and one polygon
                if (body_list[i].shape == Circle) {
                    if (sat_circles_polygons(&body_list[i], &body_list[j], &v, &temp)) {
                        colliding[i] = colliding[j] = true;
                    }
                } else {
                    if (sat_circles_polygons(&body_list[j], &body_list[i], &v, &temp)) {
                        colliding[i] = colliding[j] = true;
                    }
                }
            }
        }
    }

    // Draw using collision flags
    for (int i = 0; i < body_count; ++i) {
        Color color = colliding[i] ? RED : body_list[i].color;
        switch (body_list[i].shape) {
            case Circle:
                DrawCircleV((vec){body_list[i].position.x, -body_list[i].position.y}, body_list[i].radius, color);
                break;
            case Box: {
                vec p[4] = {
                    body_list[i].transformed_vertices.array[0], // top-left
                    body_list[i].transformed_vertices.array[1], // top-right
                    body_list[i].transformed_vertices.array[2], // bottom-right
                    body_list[i].transformed_vertices.array[3]  // bottom-left
                };
                for (int k = 0; k < 4; k++) p[k].y = -p[k].y;
                DrawLineV(p[0], p[1], color);
                DrawLineV(p[1], p[2], color);
                DrawLineV(p[2], p[3], color);
                DrawLineV(p[3], p[0], color);
            } break;
            default:
                break;
        }
    }

    free(colliding);
    return;
 }