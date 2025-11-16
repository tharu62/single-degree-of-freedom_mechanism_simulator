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
    sum_ref(&body->position, &amount);
    return;
}

void move_to(rigid_body* body, vec new_position){
    body->position = new_position;
}


void init_circle_body(vec position, float density, float mass, 
    float restitution, bool static_, float radius, Color color, rigid_body* body){

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
    
    return;
}   

void init_box_body(vec position, float density, float mass, 
    float restitution, bool static_, float width, float height, Color color, rigid_body* body){

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

    return;
}


void compute_acceleration(rigid_body* body){
    // garvity + external forces.
    return;
}

void compute_position(rigid_body* body, float dt){

    return;
}

void compute_rotation(rigid_body* body){

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

