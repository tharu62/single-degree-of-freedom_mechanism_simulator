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
 * @brief Shapes are rapresentations of 2d objects but ideally they rapresent a 3d object constrained in a 2d plane P := { P(x,y,z) : x=apha; y=beta; z=0;}.
 * Therefore these objects can have mass similar to their 3d rapresentation if we consider an arbitrary value (default=1.0f) as their thickness.
 * The main difference between the shapes, codewise, is the number of vertices they contain.
 * @param Circle has value 0 and no vertices.
 * @param Box has value 1 and 4 vertices
 * @param Polygon has value 2 and N arbitrary vertices
 */
typedef enum {
    Circle=0,       // 0 vertices
    Box=1,           // 4 vertices
    Polygon=2      // N arbitrary vertices 
} shape_type;

/**
 * @brief A standard Rotation Matrix from Linear Algebra containing the minimum amout of information for the computation. 
 * It is meant for rotation of vectors of type Vector2 vec = {x, y}.
 * @brief REMEMBER : the rotation matrix applies a rotation to a vector from the origin of the coordinate system.
 * @param x (float) relative coordinate-x of the object to rotate from the origin ( => not absolute position)
 * @param y (float) relative coordinate-y of the object to rotate from the origin ( => not absolute position)
 * @param sin (float) sine of the angle of rotation to apply. The angle must be in radiants.
 * @param cos (float) cos of the angle of rotation to apply. The angle must be in radiants.
 */
typedef struct {
    float x;
    float y;
    float sin;
    float cos;
} rotation_matrix;

/**
 * @brief A standard dinamyc array for Vector2.
 * @param array (vec*) is the array of type Vector2 to dynimically allocate.
 * @param len (int) is the lenght of the array.
 */
typedef struct {
    vec* array;
    int len;
} vec_array;

/**
 * @brief A standards dinamyc array for int.
 * @param array (int*) is the array of type int to dynimically allocate.
 * @param len (int) is the lenght of the array.
 */
typedef struct {
    int* array;
    int len;
} int_array;

/**
 * @brief A rigid body is a body of wich two random points always mantain the same distance over time. In other words, it cannot deform.
 * @param shape (shape_type)
 * @param color (Color)
 * @param position (Vector2) is the absolute position of the rigid_body in 2d space.
 * @param linear_vel (Vecotor2)
 * @param rotation (float)
 * @param rotational_vel (float)
 *  @param density (float)
 *  @param mass (float)
 *  @param restitution (float)
 *  @param area (float)
 *  @param static_ (bool)
 *  @param radius (float)
 *  @param width (float)
 *  @param height (float)
 *  @param to_transform (bool)
 * @param vertices (vec_array) is the array containing the vertices of the body relative to the origin of the coordinate system. 
 * This means the absolute position of each vertices is calculated by adding <position> .
 * @param transformed_vertices (vec_array) is the array containing the vertices transformed in their absolute position after addition of the position
 *  vector and rotation (if needed) .
 * @param triangles (int_array) ???
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
    bool to_transform;
    int_array triangles;
    vec_array vertices;
    vec_array transformed_vertices;
} rigid_body;

/**
 * @brief returns the minimum between the two given floats.
 * @param a (float)
 * @param b (float) 
 */
float min(float a, float b);

/**
 * @brief Adds <amount> to the absolute position of the given rigid_body.
 * 
 * Absolute position is modified and the <to_transform> flag is set to true. 
 * This is to ensure the fact that the transformed_vertices of the rigid_body (if they exist) must be updated to their new absolute position.
 * @param body (rigid_body*) 
 * @param amount (Vector2) 
 */
void move(rigid_body* body, vec amount);

/**
 * @brief Change the absolute position of the given rigid_body to the <new_position>.
 * The absolute position is modified and the <to_transform> flag is set to true. 
 * This is to ensure the fact that the transformed_vertices of the rigid_body (if they exist) must be updated to their new absolute position. 
 * @param body (rigid_body*)
 * @param new_position (Vector2) 
 */
void move_to(rigid_body* body, vec new_position);

/**
 * @brief 
 */
void project_vertices(vec_array* vertices, vec axis, float* min, float* max);

/**
 * @brief
 * 
 */
void project_circle(rigid_body* circle, vec axis, float* min, float* max);

/**
 * 
 */
bool sat_polygons(vec_array* vertA, vec_array* vertB, vec *normal, float* depth);

/**
 * 
 */
bool sat_circles_polygons(rigid_body* circle, rigid_body* polygon, vec* normal, float* depth);

/**
 * 
 */
bool circles_collide(rigid_body* circle1, rigid_body* circle2);

/**
 * 
 */
void rotate(rigid_body* body, float amount);

/**
 * 
 */
void init_transform_matrix(rotation_matrix* t, vec* pos, float angle);

/**
 * 
 */
void transform(vec* t_v, vec* v, rotation_matrix* t);

/**
 * 
 */
void transform_vertices(rigid_body* body);

/**
 * 
 */
void init_circle_body(vec position, float density, float mass, float restitution, bool static_, float radius, Color color, rigid_body* body);

/**
 * 
 */
void init_box_vertices(vec* vertices, float width, float height);

/**
 * 
 */
void init_box_transformed_vertices(rigid_body* body);

/**
 * 
 */
void init_box_triangles(int* triangles);

/**
 * 
 */
void init_box_body(vec position, float density, float mass, float restitution, bool static_, float width, float height, Color color, rigid_body* body);

/**
 * 
 */
void compute_acceleration(rigid_body* body);

/**
 * 
 */
void compute_collisions_circles(rigid_body* circle1, rigid_body* circle2);

/**
 * 
 */
void compute_collisions_polygons(rigid_body* body_list, rigid_body* body);

/**
 * 
 */
void compute_position(rigid_body* body, int body_count, float dt);

#endif // BODY_H