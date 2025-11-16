#ifndef BODY_H
#define BODY_H

#include <stdbool.h>
#include <math.h>
#include "raylib.h"
#include "vector.h"
#include "RK4.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/** 
 * @brief Shapes are of 2d objects but ideally they rapresent a 3d object constrained in the 2d plane z=0
 */
typedef enum {
    Circle=0,
    Box=1
} shape_type;

typedef struct{
    // float x;
    // float y;
    float sin;
    float cos;
} rotation_matrix;

/**
 * @brief A rigid body is a body of wich two random points always mantain the same distance over time. In other words, it cannot deform.
 */ 
typedef struct{
    shape_type shape;
    Color color;
    vec position;
    vec linear_vel;
    float rotation;
    float rotational_vel;
    float density;
    float mass;
    float restitution;
    float area;
    bool static_;
    float radius;
    float width;
    float height;
    vec* vertices;
    vec* transformed_vertices;
    int* triangles;
    bool to_transform;
} rigid_body;

//
void move(rigid_body* body, vec amount);

//
void move_to(rigid_body* body, vec new_position);

//
void rotate(rigid_body* body, float amount);

//
void init_transform_matrix(rotation_matrix* t, vec* pos, float angle);

//
void transform(vec* v, rotation_matrix* t);

//
void rotate_vertices(rigid_body* body);

//
void init_circle_body(vec position, float density, float mass, float restitution, bool static_, float radius, Color color, rigid_body* body);

//
void init_box_vertices(vec* vertices, float width, float height);

//
void init_box_transformed_vertices(vec* transformed_vertices, vec* vertices);

//
void init_box_triangles(int* triangles);

//
void init_box_body(vec position, float density, float mass, float restitution, bool static_, float width, float height, Color color, rigid_body* body);

//
void compute_acceleration(rigid_body* body);

//
void compute_position(rigid_body* body, int body_count, float dt);

//
void compute_collisions_circles(rigid_body* circle1, rigid_body* circle2);

#endif // BODY_H