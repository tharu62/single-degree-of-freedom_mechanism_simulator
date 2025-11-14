#ifndef BODY_H
#define BODY_H

#include "vector.h"

/** 
 * @brief Shapes are of 2d objects but ideally they rapresent a 3d object constrained in the 2d plane z=0
 */
typedef enum {
    disk=0,
    cube=1,
    bar=2
} shapes;

/**
 * @brief A rigid body is a body of wich two random points always mantain the same distance over time. In other words, it cannot deform.
 * 
 */ 
typedef struct{
    shapes shape;
    vec vertices[20];
    vec velocity;
    vec acceleration;
    vec centerOfMass;
    float mass;
} rigid_body;


void init_rigid_body(vec verteces[20], vec vel, vec acc, vec com, float mass, rigid_body* body);


void compute_position(rigid_body* body);


void compute_acceleration(rigid_body* body);


void compute_rotation(rigid_body* body);


void compute_collisions(rigid_body* body);

#endif // BODY_H