#include "body.h"

// typedef enum {
//     Circle=0,
//     Box=1
// } shape_type;

// typedef struct{
//     shape_type shape;
//     vec position;
//     vec linear_vel;
//     float rotation;
//     float rotational_vel;
//     float density;
//     float mass;
//     float restitution;
//     float area;
//     bool static_;
//     float radius;
//     float width;
//     float height;
// } rigid_body;

void move(rigid_body* body, vec amount){
    body->position.x += amount.x;
    body->position.y += amount.y;
    body->to_transform = true;
    return;
}

void move_to(rigid_body* body, vec new_position){
    body->position = new_position;
    body->to_transform = true;
}

void rotate(rigid_body* body, float amount){
    body->rotation += amount;
    body->to_transform = true;
}

void init_transform_matrix(rotation_matrix* t, vec* pos, float angle){
    // t->x = pos->x;
    // t->y = pos->y;
    t->cos = cosf(angle);
    t->sin = sinf(angle);
}

void transform(vec* v, rotation_matrix* t){
    // float rx = t->cos * v->x - t->sin * v->y;
    // float ry = t->sin * v->x + t->cos * v->y;
    // v->x = rx + t->x;
    // v->y = ry + t->y;
    v->x = v->x * t->cos - v->y * t->sin;
    v->y = v->x * t->sin + v->y * t->cos;
}

void rotate_vertices(rigid_body* body){
    if (body->to_transform){
        rotation_matrix t;
        init_transform_matrix(&t, &body->position, body->rotation);
        for(int i=0; i<4; ++i){
            transform(&body->transformed_vertices[i], &t);
        }
    }
    body->to_transform = false;
}

void init_circle_body(vec position, float density, float mass, float restitution, bool static_, float radius, Color color, rigid_body* body){

    body->shape = Circle;    
    body->color = color;    
    body->position = position;
    body->density = density;
    body->restitution = restitution;
    body->area = radius * M_PI;
    if (mass != 0) body->mass = mass;
    else body->mass = body->area * density;
    body->static_ = static_;
    body->radius = radius;
    body->vertices = NULL;
    body->transformed_vertices = NULL;  
    body->triangles = NULL;
    body->to_transform = false;
    return;
}   

void init_box_vertices(vec* vertices, float width, float height){
    float left = -width / 2.f;
    float right = width / 2.f;
    float bottom = -height / 2.f;
    float top = height / 2.f;

    vertices[0] = (vec){left,top};
    vertices[1] = (vec){right,top};
    vertices[2] = (vec){right,bottom};
    vertices[3] = (vec){left,bottom};
    return;
}

void init_box_transformed_vertices(vec* transformed_vertices, vec* vertices){
    for(int i=0; i<4; ++i){
        transformed_vertices[i] = vertices[i];
    }
    return;
}

void init_box_triangles(int* triangles){
    triangles[0] = 0;
    triangles[1] = 1;
    triangles[2] = 2;
    triangles[3] = 0;
    triangles[4] = 2;
    triangles[5] = 3;
}

void init_box_body(vec position, float density, float mass, float restitution, bool static_, float width, float height, Color color, rigid_body* body){

    body->shape = Box;
    body->color = color;    
    body->position = position;
    body->density = density;
    body->restitution = restitution;
    body->area = width * height;
    if (mass != 0) body->mass = mass;
    else body->mass = body->area * density;
    body->width = width;
    body->height = height;
    body->static_ = static_;
    body->vertices = malloc(sizeof(vec)*4);
    init_box_vertices(body->vertices, width, height);
    body->transformed_vertices = malloc(sizeof(vec)*4);
    init_box_transformed_vertices(body->transformed_vertices, body->vertices);
    body->triangles = malloc(sizeof(int)*6);
    init_box_triangles(body->triangles);
    body->to_transform = true;
    return;
}

void compute_acceleration(rigid_body* body){
    // garvity + external forces.
    return;
}

void compute_collisions_circles(rigid_body* circle1, rigid_body* circle2){
    vec normal;
    sub_val(&circle2->position, &circle1->position, &normal);
    normalize_ref(&normal);
    float distance = dist(circle1->position, circle2->position);
    float radii = circle1->radius + circle2->radius;
    float depth = radii - distance;
    if(distance < radii){ // collision
        vec temp1;
        vec temp2;
        mult_const_val(&normal, -depth, &temp1);
        div_const_ref(&temp1, 2.f);
        mult_const_val(&normal, depth, &temp2);
        div_const_ref(&temp2, 2.f);
        move(circle1, temp1);
        move(circle2, temp2);
    }
    return;
}

void compute_position(rigid_body* body_list, int body_count, float dt){
    // resolve colllisions
    // for (int i=0; i< body_count; ++i) {
    //     for (int j=0; j<body_count; ++j){
    //         if (i!=j) compute_collisions_circles(&body_list[i], &body_list[j]);
    //     }
    // }

    for (int i=0; i<body_count; ++i) {
        rotate(&body_list[i], M_PI / 2.f * dt);
        // rotate_vertices(&body_list[i]);
    }

    return;
}


