#ifndef VECTOR_H
#define VECTOR_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

/******************************************* VECTOR ALGEBRA ******************************/

#define vec Vector2

/**
 * @brief Add two vectors (a + b) and store result in c.
 * @param a first addend
 * @param b second addend
 * @param c out parameter receiving the sum
 */
void sum_val(vec* a, vec* b, vec* c);


/**
 * @brief Subtract two vectors (a - b) and store result in c.
 * @param a minuend
 * @param b subtrahend
 * @param c out parameter receiving the difference
 */
void sub_val(vec* a, vec* b, vec* c);


/**
 * @brief Add vector b to a in-place (a += b).
 * @param a vector to be modified
 * @param b vector to add
 */
void sum_ref(vec* a, vec* b);


/**
 * @brief Subtract vector b from a in-place (a -= b).
 * @param a vector to be modified
 * @param b vector to subtract
 */
void sub_ref(vec* a, vec* b);


/**
 * @brief Add a scalar to both components of a and store in c (c = a + b).
 * @param a input vector
 * @param b scalar to add
 * @param c out parameter receiving the result
 */
void sum_const_val(vec* a, float b, vec* c);


/**
 * @brief Add a scalar to both components of a in-place (a += b).
 * @param a vector to modify
 * @param b scalar to add
 */
void sum_const_ref(vec* a, float b);


/**
 * @brief Subtract a scalar from both components of a and store in c (c = a - b).
 * @param a input vector
 * @param b scalar to subtract
 * @param c out parameter receiving the result
 */
void sub_const_val(vec* a, float b, vec* c);


/**
 * @brief Subtract a scalar from both components of a in-place (a -= b).
 * @param a vector to modify
 * @param b scalar to subtract
 */
void sub_const_ref(vec* a, float b);


/**
 * @brief Multiply vector a by scalar b and store in c (c = a * b).
 * @param a input vector
 * @param b scalar multiplier
 * @param c out parameter receiving the result
 */
void mult_const_val(vec* a, float b, vec* c);


/**
 * @brief Multiply vector a by scalar b in-place (a *= b).
 * @param a vector to modify
 * @param b scalar multiplier
 */
void mult_const_ref(vec* a, float b);


/**
 * @brief Divide vector a by scalar b and store in c (c = a / b). Exits on division by zero.
 * @param a input vector
 * @param b scalar divisor
 * @param c out parameter receiving the result
 */
void div_const_val(vec* a, float b, vec* c);


/**
 * @brief Divide vector a by scalar b in-place (a /= b). Exits on division by zero.
 * @param a vector to modify
 * @param b scalar divisor
 */
void div_const_ref(vec* a, float b);


/**
 * @brief 2D cross product (scalar) for vectors a and b.
 * @param a first vector
 * @param b second vector
 * @return float scalar cross product (a.x*b.y - a.y*b.x)
 */
float cross_product(vec a, vec b);


/**
 * @brief Dot product (scalar) for vectors a and b.
 * @param a first vector
 * @param b second vector
 * @return float dot product (a.x*b.x + a.y*b.y)
 */
float dot_product(vec a, vec b);


/**
 * @brief Length (magnitude) of a 2D vector.
 * @param a input vector
 * @return float Euclidean length
 */
float len(vec a);


/**
 * @brief Distance between two 2D points/vectors.
 * @param a first point
 * @param b second point
 * @return float Euclidean distance
 */
float dist(vec a, vec b);


/**
 * @brief Angle between two vectors in radians.
 * @param a first vector
 * @param b second vector
 * @return float angle in radians
 */
float angle(vec a, vec b);


/**
 * @brief Normalize vector a and store result in b. If a is near-zero returns unit x-axis.
 * @param a input vector
 * @param b out parameter receiving the normalized vector
 */
void normalize_val(vec *a, vec* b);


/**
 * @brief Normalize vector a in-place. If a is near-zero it becomes the unit x-axis.
 * @param a vector to normalize in-place
 */
void normalize_ref(vec *a);

#endif // VECTOR_H