#ifndef VECTOR_H
#define VECTOR_H

// vettore 2d
typedef struct {}vec;

// prodotto vettoriale per vettori 2d
float cross_product(vec a, vec b);

// prodotto scalare per vettori 2d
float dot_product(vec a, vec b);

// norma di un vettore 2d
float norm(vec a);

// distanza tra due vettori 2d
float dist(vec a, vec b);

// angolo tra due vettori 2d
float angle(vec a, vec b);

void normalize(vec *a);

#endif // VECTOR_H