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


// 
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

void compute_collisions_circles(rigid_body* circle1, rigid_body* cirlce2){
    float distance = dist(circle1->position, cirlce2->position);
    float radii = circle1->radius + cirlce2->radius;
    if(distance >= radii){

    }
    else{

    }
    return;
}


void move(rigid_body* body, vec amount){
    sum_(&body->position, &amount);
    return;
}

void move_to(rigid_body* body, vec new_position){
    body->position = new_position;
}

