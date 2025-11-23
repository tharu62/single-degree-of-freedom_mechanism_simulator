#include "body.h"

float min(float a, float b) {
    assert(a != NAN && b != NAN);
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void find_mean(vec_array* v, vec* v_out){
    float sum_x = 0.f;
    float sum_y = 0.f;

    for (int i=0; i<v->len; ++i) {
        sum_x += v->array[i].x;
        sum_y += v->array[i].y;
    }
    *v_out = (vec){sum_x/(float)v->len, sum_y/(float)v->len};
}

void move(rigid_body* body, vec amount){
    assert(amount.x != NAN && amount.y != NAN);
    body->position.x += amount.x;
    body->position.y += amount.y;
    body->to_transform = true;
    return;
}

void move_to(rigid_body* body, vec new_position){
    body->position = new_position;
    body->to_transform = true;
}

void project_vertices(vec_array* vertices, vec axis, float* min, float* max){
    for(int i=0; i<vertices->len; ++i){
        vec v = {0.f,0.f};
        v.x = vertices->array[i].x;
        v.y = vertices->array[i].y;
        float proj = dot_product(v , axis);
        if (proj < *min) { *min = proj;}
        if (proj > *max) { *max = proj;}
    }
    return;
}

void project_circle(rigid_body* circle, vec axis, float* min, float* max){
    // project circle onto an axis: if axis is normalized then
    // projection is center dot axis +/- radius
    vec n = axis;
    normalize_ref(&n);
    float center = dot_product(circle->position, n);
    *min = center - circle->radius;
    *max = center + circle->radius;
    return;
}

int find_closest_point_on_polygon(rigid_body* circle, rigid_body* polygon){
    assert(circle->position.x != NAN && circle->position.y != NAN);
    int result = -1;
    float min_dist = __FLT_MAX__;
    for(int i=0; i<polygon->transformed_vertices.len; ++i){
        vec v = polygon->transformed_vertices.array[i];
        float distance = dist(v, circle->position);
        if (distance < min_dist) {
            min_dist = distance;
            result = i;
        }
    }
    if (result == -1){
        printf("error in finding the closest point to the circle\n");
        exit(-1);
    }
    return result;
}

bool sat_polygons(vec_array* vertA, vec_array* vertB, vec *normal, float* depth){
    *normal = (vec){0.f,0.f};
    *depth = __FLT_MAX__;

    for(int i=0; i<vertA->len; ++i){
        vec va;
        va.x = vertA->array[i].x;
        va.y = vertA->array[i].y;
        vec vb;
        vb.x = vertA->array[(i+1) % vertA->len].x;
        vb.y = vertA->array[(i+1) % vertA->len].y;
        vec edge;
        sub_val(&vb, &va, &edge);
        vec axis = (vec){-edge.y, edge.x};
        normalize_ref(&axis);
        float minA = __FLT_MAX__;
        float maxA = -__FLT_MAX__;
        float minB = __FLT_MAX__;
        float maxB = -__FLT_MAX__;
        project_vertices(vertA, axis, &minA, &maxA);
        project_vertices(vertB, axis, &minB, &maxB);
        if(minA >= maxB || minB >= maxA){ // found separation
            return false;
        }
        float axis_depth = min(maxB - minA, maxA - minB);
        if (axis_depth < *depth) {
            *depth = axis_depth;
            *normal = axis;
        }
    }

    for(int i=0; i<vertB->len; ++i){
        vec va;
        va.x = vertB->array[i].x;
        va.y = vertB->array[i].y;
        vec vb;
        vb.x = vertB->array[(i+1) % vertB->len].x;
        vb.y = vertB->array[(i+1) % vertB->len].y;
        vec edge;
        sub_val(&vb, &va, &edge);
        vec axis = (vec){-edge.y, edge.x};
        normalize_ref(&axis);
        float minA = __FLT_MAX__;
        float maxA = -__FLT_MAX__;
        float minB = __FLT_MAX__;
        float maxB = -__FLT_MAX__;
        project_vertices(vertA, axis, &minA, &maxA);
        project_vertices(vertB, axis, &minB, &maxB);
        if(minA >= maxB || minB >= maxA){ // found separation
            return false;
        }
        float axis_depth = min(maxB - minA, maxA - minB);
        if (axis_depth < *depth) {
            *depth = axis_depth;
            *normal = axis;
        }
    }
    // normal is already one of the separating axes (normalized)
    normalize_ref(normal);

    vec centerA, centerB;
    find_mean(vertA, &centerA);
    find_mean(vertB, &centerB);

    vec direction;
    sub_val(&centerB, &centerA, &direction);

    if(dot_product(direction, *normal) < 0){
        *normal = (vec){-normal->x, -normal->y};
    }

    return true;
}

bool sat_circles_polygons(rigid_body* circle, rigid_body* polygon, vec* normal, float* depth){
    *normal = (vec){0.f,0.f};
    *depth = __FLT_MAX__;
    vec axis = {0.f,0.f};
    float axis_depth = 0.f;

    for(int i=0; i<polygon->transformed_vertices.len; ++i){
        vec va = polygon->transformed_vertices.array[i];
        vec vb = polygon->transformed_vertices.array[(i+1) % polygon->transformed_vertices.len];
        vec edge;
        sub_val(&vb, &va, &edge);
        axis = (vec){-edge.y, edge.x};
        normalize_ref(&axis);

        float minA = __FLT_MAX__;
        float maxA = -__FLT_MAX__;
        float minB = __FLT_MAX__;
        float maxB = -__FLT_MAX__;
        project_vertices(&polygon->transformed_vertices, axis, &minA, &maxA);
        project_circle(circle, axis, &minB, &maxB);

        if(minA >= maxB || minB >= maxA){ // found separation
            return false;
        }

        axis_depth = min((maxB - minA), (maxA - minB));
        if (axis_depth < *depth) {
            *depth = axis_depth;
            *normal = axis;
        }
    }

    int closest_point_index = find_closest_point_on_polygon(circle, polygon);
    vec cp = polygon->transformed_vertices.array[closest_point_index];
    sub_val(&cp, &circle->position, &axis);
    normalize_ref(&axis);

    float minA = __FLT_MAX__;
    float maxA = -__FLT_MAX__;
    float minB = __FLT_MAX__;
    float maxB = -__FLT_MAX__;
    project_vertices(&polygon->transformed_vertices, axis, &minA, &maxA);
    project_circle(circle, axis, &minB, &maxB);

    if(minA >= maxB || minB >= maxA){ // found separation
        return false;
    }
    axis_depth = min(maxB - minA, maxA - minB);
    if (axis_depth < *depth) {
        *depth = axis_depth;
        *normal = axis;
    }

    // normal is stored already normalized
    normalize_ref(normal);

    vec polygon_center;
    find_mean(&polygon->transformed_vertices, &polygon_center);

    vec direction;
    sub_val(&polygon_center, &circle->position, &direction);

    if(dot_product(direction, *normal) < 0){
        *normal = (vec){-normal->x, -normal->y};
    }

    if(normal->x == NAN || normal->y == NAN || *depth == NAN){
        printf("error in calculating normal and depht");
        exit(-1);
    }

    return true;
}

bool circles_collide(rigid_body* circle1, rigid_body* circle2){
    vec normal={0.f,0.f};
    sub_val(&circle2->position, &circle1->position, &normal);
    normalize_ref(&normal);
    float distance = dist(circle1->position, circle2->position);
    float radii = circle1->radius + circle2->radius;
    if(distance < radii){ // collision
        return true;
    }
    return false;           // no collision
}

void rotate(rigid_body* body, float amount){
    assert(amount != NAN);
    body->rotation += amount;
    body->to_transform = true;
}

void init_transform_matrix(rotation_matrix* t, vec* pos, float angle){
    t->x = pos->x;
    t->y = pos->y;
    t->cos = cosf(angle);
    t->sin = sinf(angle);
}

void transform(vec* t_v, vec* v, rotation_matrix* t){
    t_v->x = v->x * t->cos - v->y * t->sin + t->x;
    t_v->y = v->x * t->sin + v->y * t->cos + t->y;
}

void transform_vertices(rigid_body* body){
    if ( body->to_transform ) 
    {
        rotation_matrix t;
        init_transform_matrix(&t, &body->position, body->rotation);
        for(int i=0; i<body->transformed_vertices.len; ++i){
            transform(&body->transformed_vertices.array[i], &body->vertices.array[i], &t);
        }
    }
    body->to_transform = false;
}

void init_circle_body(vec position, float density, float mass, float restitution, bool static_, float radius, Color color, rigid_body* body){

    body->shape         = Circle;    
    body->color         = color;    
    body->position      = position;
    body->linear_vel   = (vec){0.f,0.f};
    body->rotation      = 0.f;
    body->rotational_vel = 0.f;
    body->density       = density;
    body->restitution   = restitution;
    body->area          = radius * PI;
    body->static_       = static_;
    body->radius        = radius;
    body->width         = 0.f;
    body->height        = 0.f;
    body->to_transform  = true;

    if (mass != 0) 
        body->mass = mass;
    else 
        body->mass = body->area * density;
    
    body->vertices.array = NULL;
    body->vertices.len   = 0;

    body->transformed_vertices.array = NULL;
    body->transformed_vertices.len   = 0;  

    body->triangles.array = NULL;
    body->triangles.len   = 0;
    return;
}   

void init_box_vertices(vec* vertices, float width, float height){
    float left      = -width / 2.f;
    float right     =  width / 2.f;
    float bottom    = -height / 2.f;
    float top       =  height / 2.f;

    vertices[0] = (vec){left,top};
    vertices[1] = (vec){right,top};
    vertices[2] = (vec){right,bottom};
    vertices[3] = (vec){left,bottom};
    return;
}

void init_box_transformed_vertices(rigid_body* body){
    for(int i=0; i<body->transformed_vertices.len; ++i){
        body->transformed_vertices.array[i].x = body->vertices.array[i].x + body->position.x;
        body->transformed_vertices.array[i].y = body->vertices.array[i].y + body->position.y;
    }
    return;
}

void init_box_triangles(int* triangles){
    triangles[0] = 0;
    triangles[1] = 1;
    triangles[2] = 2;
    triangles[3] = 0;
    triangles[4] = 2;
    triangles[5] = 3;
}

void init_box_body(vec position, float density, float mass, float restitution, bool static_, float width, float height, Color color, rigid_body* body){

    body->shape         = Box;
    body->color         = color;    
    body->position      = position;
    body->linear_vel   = (vec){0.f,0.f};
    body->rotation      = 0.f;
    body->rotational_vel = 0.f;
    body->density       = density;
    body->restitution   = restitution;
    body->area          = width * height;
    body->static_       = static_;
    body->radius        = 0.f;
    body->width         = width;
    body->height        = height;
    body->to_transform  = true;

    if (mass != 0) 
        body->mass = mass;
    else 
        body->mass = body->area * density;
    
    body->vertices.len   = 4; 
    body->vertices.array = malloc(sizeof(vec)*body->vertices.len);
    init_box_vertices(body->vertices.array, width, height);

    body->transformed_vertices.len   = 4;
    body->transformed_vertices.array = malloc(sizeof(vec)*body->transformed_vertices.len);
    init_box_transformed_vertices(body);
    
    body->triangles.len   = 6;
    body->triangles.array = malloc(sizeof(int)*body->triangles.len);
    init_box_triangles(body->triangles.array);
    return;
}

// unused
void compute_acceleration(rigid_body* body){
    // garvity + external forces.
    return;
}

void compute_collisions_circles(rigid_body* circle1, rigid_body* circle2){
    if (!circles_collide(circle1, circle2)) return; 
    vec normal;
    sub_val(&circle2->position, &circle1->position, &normal);
    normalize_ref(&normal);
    float distance = dist(circle1->position, circle2->position);
    float radii = circle1->radius + circle2->radius;
    float depth = radii - distance;
    if(distance < radii){ // collision
        vec temp1;
        vec temp2;
        mult_const_val(&normal, -depth, &temp1);
        div_const_ref(&temp1, 2.f);
        mult_const_val(&normal, depth, &temp2);
        div_const_ref(&temp2, 2.f);
        move(circle1, temp1);
        move(circle2, temp2);
    }
    return;
}

void compute_collisions_polygons(rigid_body* bodyA, rigid_body* bodyB){
    vec normal={0.f,0.f};
    float depth=0.f;
    if(sat_polygons(&bodyA->transformed_vertices, &bodyB->transformed_vertices, &normal, &depth) ){
        move(bodyA, (vec){-normal.x * depth / 2.f, -normal.y * depth / 2.f});
        move(bodyB, (vec){normal.x * depth / 2.f, normal.y * depth / 2.f});
        transform_vertices(bodyA);
        transform_vertices(bodyB);
    }
    return;
}

void compute_collisions_circles_polygon(rigid_body* circle, rigid_body* polygon){
    vec normal = {0.f,0.f};
    float depth = 0.f;
    if(sat_circles_polygons(circle, polygon, &normal, &depth)){
        move(circle, (vec){-normal.x * depth / 2.f, -normal.y * depth / 2.f});
        move(polygon, (vec){normal.x * depth / 2.f, normal.y * depth / 2.f}); //only moves center of polygon
        transform_vertices(polygon);
    }
    return;
}

/**
 * @todo more efficient updating method ...
 */
void compute_position(rigid_body* body_list, int body_count, float dt){
    
    for(int i=0; i<body_count; ++i){

        for (int j=0; j<body_count; ++j) {

            if (i!=j) {

                if (body_list[i].shape == Circle) {

                    // i =  circle, j = circle
                    if (body_list[j].shape ==  Circle) {
                        compute_collisions_circles(&body_list[i], &body_list[j]);
                    }
                    
                    // i= circle, j = box
                    if (body_list[j].shape == Box) {
                        // printf("coll 1, index: %d\n", i);
                        compute_collisions_circles_polygon(&body_list[i], &body_list[j]);
                    }
                }

                if (body_list[i].shape == Box) {

                    // rotate(&body_list[i], (float) (PI / 2.f * dt));
                    transform_vertices(&body_list[i]);
                    
                    // i = box, j = circle
                    if (body_list[j].shape ==  Circle) {
                        // printf("coll 2\n");
                        compute_collisions_circles_polygon(&body_list[j], &body_list[i]);
                    }
                    // i = box, j = box
                    if (body_list[j].shape == Box) {
                        compute_collisions_polygons(&body_list[i], &body_list[j]);
                    }
                }
            }
        
        }
    }

    return;
}