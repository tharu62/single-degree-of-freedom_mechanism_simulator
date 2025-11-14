#include "RK4.H"

// velcocity = x(t) = dx(t) / dt or 
// 
void compute(vec* acc(float x, float y), vec* pos, vec*k2, vec* k3, vec* k4, float dt){

    vec k1 ={dt*acc(pos->x,pos->y)->x, dt*acc(pos->x,pos->y)->y};
    vec k2;
    vec k3;
    vec k4;

    pos->x = pos->x + (dt / 6.0) * (k1.x + 2*k2->x + 2*k3->x + k4->x);
    pos->y = pos->y + (dt / 6.0) * (k1.y + 2*k2->y + 2*k3->y + k4->y);
}