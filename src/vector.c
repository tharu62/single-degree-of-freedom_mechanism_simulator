#include "vector.h"


/********************************** VECTOR OPERATIONS ****************************************/

// somma di vettori 2d, modifica c
void sum_val(vec* a, vec* b, vec* c){
    c->x = a->x + b->x;
    c->y = a->y + b->y;
    return;
}

// sottrazione di vettori 2d, modifica c
void sub_val(vec* a, vec* b, vec* c){
    c->x = a->x - b->x;
    c->y = a->y - b->y;
    return;
}

// somma di vettori 2d, modifica a
void sum_ref(vec* a, vec* b){
    a->x = a->x + b->x;
    a->y = a->y + b->y;
    return;
}

// sottrazione di vettori 2d, modifica a
void sub_ref(vec* a, vec* b){
    a->x = a->x - b->x;
    a->y = a->y - b->y;
    return;
}

// somma di un vettore con una costante, modifica c
void sum_const_val(vec* a, float b, vec* c){
    c->x = a->x + b;
    c->y = a->y + b;
    return;
}

// somma di un vettore con una costante, mdifica a
void sum_const_ref(vec* a, float b){
    a->x = a->x + b;
    a->y = a->y + b;
    return;
}


// sottrazione di un vettore con una costante, modifica c
void sub_const_val(vec* a, float b, vec* c){
    c->x = a->x - b;
    c->y = a->y - b;
    return;
}

// sottrazione di un vettore con una costante, moifica a
void sub_const_ref(vec* a, float b){
    a->x = a->x - b;
    a->y = a->y - b;
    return;
}

// moltiplicazione di un vettore con una costante, modifica c
void mult_const_val(vec* a, float b, vec* c){
    c->x = a->x * b;
    c->y = a->y * b;
    return;
}

// moltiplicazione di un vettore con una costante, modifica a
void mult_const_ref(vec* a, float b){
    a->x = a->x * b;
    a->y = a->y * b;
    return;
}

// divisione di un vettore con una costante, modifica c
void div_const_val(vec* a, float b, vec* c){
    if(b != 0.0){
        c->x = a->x / b;
        c->y = a->y / b;
        return;
    }
    else{
        printf("error : division by 0");
        exit(1);
    }
}

// divisione di un vettore con una costante, modifica a
void div_const_ref(vec* a, float b){
    if(b != 0.0){
        a->x = a->x / b;
        a->y = a->y / b;
        return;
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

// normalizzazione di un vettore 2d, modifica b
void normalize_val(vec *a, vec* b){
    float len_ = sqrt(a->x * a->x + a->y*a->y);
    if (len_ < 1e-8f) {
        // b->x = 1.f;
        // b->y = 0.f;
        return;
    }
    b->x = a->x / len_;
    b->y = a->y / len_;
    return;
}

// normalizzazione di un vettore 2d, modifica a
void normalize_ref(vec *a){
    float len_ = sqrt(a->x * a->x + a->y*a->y);
    if (len_ < 1e-8f) {
        // a->x = 1.f;
        // a->y = 0.f;
        return;
    }
    a->x = a->x / len_;
    a->y = a->y / len_;
    return;
}


/**********************************************************************************************/
