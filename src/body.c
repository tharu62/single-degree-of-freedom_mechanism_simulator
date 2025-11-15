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
    float restitution, bool static_, float radius, float width, float height, rigid_body* body){

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

void compute_collisions(rigid_body* body){

    return;
}

