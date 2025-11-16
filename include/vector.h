#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define vec Vector2

// // vettore 2d
// typedef struct{
//     float x;
//     float y;
// } Vector2;

// somma di vettori 2d, modifica c
void sum_val(vec* a, vec* b, vec* c);

// sottrazione di vettori 2d, modifica c
void sub_val(vec* a, vec* b, vec* c);

// somma di vettori 2d, modifica a
void sum_ref(vec* a, vec* b);

// sottrazione di vettori 2d, modifica a
void sub_ref(vec* a, vec* b);

// somma di un vettore con una costante, modifica c
void sum_const_val(vec* a, float b, vec* c);

// somma di un vettore con una costante, mdifica a
void sum_const_ref(vec* a, float b);

// sottrazione di un vettore con una costante, modifica c
void sub_const_val(vec* a, float b, vec* c);

// sottrazione di un vettore con una costante, moifica a
void sub_const_ref(vec* a, float b);

// moltiplicazione di un vettore con una costante, modifica c
void mult_const_val(vec* a, float b, vec* c);

// moltiplicazione di un vettore con una costante, modifica a
void mult_const_ref(vec* a, float b);

// divisione di un vettore con una costante, modifica c
void div_const_val(vec* a, float b, vec* c);

// divisione di un vettore con una costante, modifica a
void div_const_ref(vec* a, float b);

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

// normalizzazione di un vettore 2d, modifica b
void normalize_val(vec *a, vec* b);

// normalizzazione di un vettore, modifica a
void normalize_ref(vec *a);

#endif // VECTOR_H