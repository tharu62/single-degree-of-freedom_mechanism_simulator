#include "body.h"

/**
 * 
 */
void init_rigid_body(vec verteces[20], vec vel, vec acc, vec com, float mass, rigid_body* body){
    body->shape = disk;
    for(int i=0; i<20; ++i){
        body->vertices[i] = verteces[i];
    }
    body->velocity = vel;
    body->acceleration = acc;
    body->centerOfMass = com;
    body->mass = mass;
    return;
}   

/**
 * @brief Updating the position of each vertex of the body using RK4 (Runge Kutta 4)
 * @todo all
 */
void compute_position(rigid_body* body){
    switch ( body->shape )
    {
        case disk:
            
            break;
        case cube:

            break;
        case bar:

            break;
        default:
            return;
    }
    return;
}

/**
 * @todo all
 */
void compute_acceleration(rigid_body* body){
    switch ( body->shape )
    {
        case disk:
            
            break;
        case cube:

            break;
        case bar:

            break;
        default:
            return;
    }
    return;
}

/**
 * @todo all
 */
void compute_rotation(rigid_body* body){
    switch ( body->shape )
    {
        case disk:
            
            break;
        case cube:

            break;
        case bar:

            break;
        default:
            return;
    }
    return;
}

/**
 * @todo all
 */
void compute_collisions(rigid_body* body){
    switch ( body->shape )
    {
        case disk:
            
            break;
        case cube:

            break;
        case bar:

            break;
        default:
            return;
    }
    return;
}

