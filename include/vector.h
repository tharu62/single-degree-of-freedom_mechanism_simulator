#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// vettore 2d
typedef struct{
    float x;
    float y;
} vec;

// somma tra vettori
vec sum_(vec* a, vec* b);

// sottrazione tra vettori
vec sub_(vec* a, vec* b);

// somma di un vettore con una costante
vec sum_const(vec* a, float b);

// sottrazione di un vettore con una costante
vec sub_const(vec* a, float b);

// prodotto di un vettore con una costante
vec mult_const(vec* a, float b);

// divisione di un vettore con una costante
vec div_const(vec* a, float b);

// prodotto vettoriale per vettori 2d
float cross_product(vec a, vec b);

// prodotto scalare per vettori 2d
float dot_product(vec a, vec b);

// lunghezza di un vettore 2d
float len(vec a);

// distanza tra due vettori 2d
float dist(vec a, vec b);

// angolo tra due vettori 2d
float angle(vec a, vec b);

// normalizzazione di un vettore
void normalize(vec *a);

#endif // VECTOR_H