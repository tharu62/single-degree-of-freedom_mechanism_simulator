#include <math.h>

// vettore 2d
typedef struct{
    float x;
    float y;
} vec;

// prodotto vettoriale per vettori 2d
float cross_product(vec a, vec b){
    return (a.x*b.y - a.y*b.x);
}

// prodotto scalare per vettori 2d
float dot_product(vec a, vec b){
    return (a.x*b.x + a.y*b.y);
}

// norma di un vettore 2d
float norm(vec a){
    return sqrt(a.x*a.x + a.y*a.y);
}

// distanza tra due vettori 2d
float dist(vec a, vec b){
    return sqrt(pow((b.x-a.x),2) + pow((b.y-a.y),2));
}

// angolo tra due vettori 2d
float angle(vec a, vec b){
    return acos(dot_product(a,b) / norm(a) * norm(b));
}

// normalizzazione di un vettore 2d
void normalize(vec *a){
    int norm = sqrt(a->x*a->x + a->y*a->y);
    a->x = a->x / norm;
    a->y = a->y / norm;
    return;
}