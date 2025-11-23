#ifndef BODY_H
#define BODY_H

#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "raylib.h"
#include "vector.h"
#include "RK4.h"

/******************************************************* BODY FUNCTIONS ********************************************************** */

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
 * @param x relative coordinate-x of the object to rotate from the origin ( => not absolute position)
 * @param y relative coordinate-y of the object to rotate from the origin ( => not absolute position)
 * @param sin sine of the angle of rotation to apply. The angle must be in radiants.
 * @param cos cos of the angle of rotation to apply. The angle must be in radiants.
 */
typedef struct {
    float x;
    float y;
    float sin;
    float cos;
} rotation_matrix;

/**
 * @brief A standard dinamyc array for Vector2.
 * @param array is the array of type Vector2 to dynimically allocate.
 * @param len is the lenght of the array.
 */
typedef struct {
    vec* array;
    int len;
} vec_array;

/**
 * @brief A standards dinamyc array for int.
 * @param array is the array of type int to dynimically allocate.
 * @param len is the lenght of the array.
 */
typedef struct {
    int* array;
    int len;
} int_array;

/**
 * @brief A rigid body is a body of wich two random points always mantain the same distance over time. In other words, it cannot deform.
 * @param shape
 * @param color
 * @param position is the absolute position of the rigid_body in 2d space.
 * @param linear_vel
 * @param rotation
 * @param rotational_vel
 *  @param density
 *  @param mass
 *  @param restitution
 *  @param area
 *  @param static_
 *  @param radius
 *  @param width
 *  @param height
 *  @param to_transform
 * @param vertices is the array containing the vertices of the body relative to the origin of the coordinate system. 
 * This means the absolute position of each vertices is calculated by adding <position> .
 * @param transformed_vertices is the array containing the vertices transformed in their absolute position after addition of the position
 *  vector and rotation (if needed) .
 * @param triangles ???
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
 * @param a
 * @param b
 */
float min(float a, float b);


/**
 * @brief Compute the arithmetic mean (centroid) of a dynamic array of vectors.
 * @param v dynamic array of vectors
 * @param v_out out parameter containing the computed mean
 */
void find_mean(vec_array* v, vec* v_out);


/**
 * @brief Adds <amount> to the absolute position of the given rigid_body.
 *
 * Absolute position is modified and the <to_transform> flag is set to true.
 * This is to ensure the fact that the transformed_vertices of the rigid_body (if they exist) must be updated to their new absolute position.
 * @param body pointer to the body to move
 * @param amount vector amount to add to the absolute position
 */
void move(rigid_body* body, vec amount);


/**
 * @brief Change the absolute position of the given rigid_body to the <new_position>.
 * The absolute position is modified and the <to_transform> flag is set to true.
 * This is to ensure the fact that the transformed_vertices of the rigid_body (if they exist) must be updated to their new absolute position.
 * @param body pointer to the body to relocate
 * @param new_position new absolute position to set
 */
void move_to(rigid_body* body, vec new_position);


/**
 * @brief Projects an array of vertices onto the given axis and returns the scalar min/max projection values.
 * @param vertices array of vertices to project (absolute/transformed positions expected)
 * @param axis axis to project onto (need not be normalized)
 * @param min out parameter for minimum projection value
 * @param max out parameter for maximum projection value
 */
void project_vertices(vec_array* vertices, vec axis, float* min, float* max);


/**
 * @brief Projects a circle onto the given axis. If the axis is normalized the projection
 * of the circle is simply center dot axis +/- radius; this function normalizes internally.
 * @param circle circle body (uses `circle->position` and `circle->radius`)
 * @param axis axis to project onto (need not be normalized)
 * @param min out parameter for minimum projection value
 * @param max out parameter for maximum projection value
 */
void project_circle(rigid_body* circle, vec axis, float* min, float* max);


/**
 * @brief Find the index of the vertex of <polygon> whose transformed position is
 * the closest to the given circle center. Useful for circle-vs-polygon SAT axis selection.
 * @param circle circle body (uses `circle->position`)
 * @param polygon polygon body (uses `polygon->transformed_vertices`)
 * @return int index of the closest transformed vertex (0..len-1)
 */
int find_closest_point_on_polygon(rigid_body* circle, rigid_body* polygon);


/**
 * @brief Separate Axis Theorem test for two polygons (or boxes). If there is no separating
 * axis the function returns true and optionally provides the penetration depth and collision normal.
 * @param vertA transformed vertices of the first polygon
 * @param vertB transformed vertices of the second polygon
 * @param normal out parameter for the collision normal (unit vector, points from A to B)
 * @param depth out parameter for penetration depth along the normal
 * @return bool true if polygons overlap (collision), false if separated
 */
bool sat_polygons(vec_array* vertA, vec_array* vertB, vec *normal, float* depth);


/**
 * @brief Separate Axis Theorem test for a circle and a polygon. Uses polygon edge normals
 * plus the axis from the circle center to the closest polygon vertex. Returns true if
 * collision is detected and fills normal/depth.
 * @param circle circle body
 * @param polygon polygon/box body
 * @param normal out parameter for the collision normal (unit vector)
 * @param depth out parameter for penetration depth along the normal
 * @return bool true if circle and polygon overlap (collision), false if separated
 */
bool sat_circles_polygons(rigid_body* circle, rigid_body* polygon, vec* normal, float* depth);


/**
 * @brief Simple circle-vs-circle overlap test (checks center distance against sum of radii).
 * @param circle1 first circle
 * @param circle2 second circle
 * @return bool true if circles overlap, false otherwise
 */
bool circles_collide(rigid_body* circle1, rigid_body* circle2);


/**
 * @brief Apply an incremental rotation to the body (adds `amount` to `rotation`)
 * and mark the body for transform update.
 * @param body body to rotate
 * @param amount rotation amount in radians to add
 */
void rotate(rigid_body* body, float amount);


/**
 * @brief Initialize a rotation_matrix used for transforming local vertices to world space.
 * @param t out parameter to fill
 * @param pos position to use as translation component
 * @param angle rotation angle in radians
 */
void init_transform_matrix(rotation_matrix* t, vec* pos, float angle);


/**
 * @brief Transform a single vector `v` by rotation/translation matrix `t` into `t_v`.
 * This produces the absolute position of a vertex given a body's transform.
 * @param t_v out parameter for transformed vector
 * @param v local vertex to transform
 * @param t transform containing cos/sin and translation
 */
void transform(vec* t_v, vec* v, rotation_matrix* t);


/**
 * @brief Transform all vertices of a body into their absolute positions using the body's
 * position and rotation. Sets `to_transform` to false after updating.
 * @param body body containing `vertices` and `transformed_vertices`
 */
void transform_vertices(rigid_body* body);


/**
 * @brief Initialize a rigid_body as a circle with given physical properties.
 * @param position initial center position
 * @param density material density
 * @param mass mass (if 0 computed from density)
 * @param restitution bounciness
 * @param static_ whether the body is static
 * @param radius circle radius
 * @param color drawing color
 * @param body out parameter to initialize
 */
void init_circle_body(vec position, float density, float mass, float restitution, bool static_, float radius, Color color, rigid_body* body);


/**
 * @brief Fill an array of 4 vertices for an axis-aligned box centered at origin.
 * @param vertices pre-allocated array of 4 vec elements
 * @param width box width
 * @param height box height
 */
void init_box_vertices(vec* vertices, float width, float height);


/**
 * @brief Initialize the `transformed_vertices` of a box by adding the body's position
 * to its local `vertices` (no rotation applied). Used for simple boxes.
 * @param body box body with `vertices` and `transformed_vertices` allocated
 */
void init_box_transformed_vertices(rigid_body* body);


/**
 * @brief Initialize the triangle index list for a box (two triangles).
 * @param triangles pre-allocated array of 6 ints
 */
void init_box_triangles(int* triangles);


/**
 * @brief Initialize a box rigid_body with provided physical properties and allocate
 * vertex/triangle arrays.
 * @param position initial position
 * @param density
 * @param mass
 * @param restitution
 * @param static_
 * @param width
 * @param height
 * @param color
 * @param body out parameter to initialize
 */
void init_box_body(vec position, float density, float mass, float restitution, bool static_, float width, float height, Color color, rigid_body* body);


/**
 * @brief Compute acceleration for a body from forces (gravity & external). TODO: implement.
 * @param body body to compute acceleration for
 */
void compute_acceleration(rigid_body* body);


/**
 * @brief Compute and apply collision response for two circles (simple positional correction).
 * @param circle1 first circle
 * @param circle2 second circle
 */
void compute_collisions_circles(rigid_body* circle1, rigid_body* circle2);


/**
 * @brief Compute and apply collision response for two polygons/boxes.
 * Uses SAT to detect overlap and applies a simple positional correction.
 * @param bodyA first polygon/box
 * @param bodyB second polygon/box
 */
void compute_collisions_polygons(rigid_body* bodyA, rigid_body* bodyB);


/**
 * @brief Compute and apply collision response for a circle and a polygon/box.
 * @param circle circle body
 * @param polygon polygon/box body
 */
void compute_collisions_circles_polygon(rigid_body* circle, rigid_body* polygon);


/**
 * @brief Update positions and perform collision checks for all bodies in the provided list.
 * This function steps the simulation for the given timestep `dt`.
 * @param body_list array of bodies
 * @param body_count number of bodies in the array
 * @param dt timestep in seconds
 */
void compute_position(rigid_body* body_list, int body_count, float dt);

#endif // BODY_H