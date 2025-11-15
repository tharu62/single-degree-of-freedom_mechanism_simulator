#include "vector.h"

// somma di vettori 2d
vec sum_(vec* a, vec* b){
    vec temp;
    temp.x = a->x + b->x;
    temp.y = a->y + b->y;
    return temp;
}

/********************************** VECTOR OPERATIONS ****************************************/
// sottrazione di vettori 2d
vec sub_(vec* a, vec* b){
    vec temp;
    temp.x = a->x - b->x;
    temp.y = a->y - b->y;
    return temp;
}

// somma di un vettore con una costante
vec sum_const(vec* a, float b){
    vec temp;
    temp.x = a->x + b;
    temp.y = a->y + b;
    return temp;
}

// sottrazione di un vettore con una costante
vec sub_const(vec* a, float b){
    vec temp;
    temp.x = a->x - b;
    temp.y = a->y - b;
    return temp;
}

// moltiplicazione di un vettore con una costante
vec mult_const(vec* a, float b){
    vec temp;
    temp.x = a->x * b;
    temp.y = a->y * b;
    return temp;
}

// divisione di un vettore con una costante
vec div_const(vec* a, float b){
    vec temp;
    if(b != 0.0){
        temp.x = a->x / b;
        temp.y = a->y / b;
        return temp;
    }
    else{
        printf("error : division by 0");
        exit(1);
    }
}

// prodotto vettoriale per vettori 2d
float cross_product(vec a, vec b){
    return (a.x*b.y - a.y*b.x);
}

// prodotto scalare per vettori 2d
float dot_product(vec a, vec b){
    return (a.x*b.x + a.y*b.y);
}

// lunghezza di un vettore 2d
float len(vec a){
    return sqrt(a.x*a.x + a.y*a.y);
}

// distanza tra due vettori 2d
float dist(vec a, vec b){
    return sqrt(pow((b.x-a.x),2) + pow((b.y-a.y),2));
}

// angolo tra due vettori 2d
float angle(vec a, vec b){
    return acos(dot_product(a,b) / len(a) * len(b));
}

// normalizzazione di un vettore 2d
void normalize(vec *a){
    float len_ = len(*a);
    a->x = a->x / len_;
    a->y = a->y / len_;
    return;
}

/**********************************************************************************************/
