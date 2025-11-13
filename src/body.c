#include "body.h"

void init_body(vec pos, vec vel, vec acc, vec com, float area, float density, rigid_body* body){
    body->position = pos;
    body->velocity = vel;
    body->acceleration = acc;
    body->centerOfMass = com;
    body->mass = area * density;
    return;
}