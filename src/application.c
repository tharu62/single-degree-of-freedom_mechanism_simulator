#include "application.h"

/*******************************************************************************************/
// window size
int screenWidth = 1280;              
int screenHeight = 720;
// Blueprint Color Scheme
const Color RoyaleBlue = {48, 87, 225};
const Color LavanderBlue = {206, 216, 247};
const Color ResolutionBlue = {0, 32, 130};

// constants
const int body_count = 1000;             // number of bodies in the simulation
const int framerate = 80;              // [fps] 
const float speed = 10.0;               // [m/s] 
/*******************************************************************************************/

void PhysicsEngineRun()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    SetTraceLogLevel(LOG_ERROR);                // Cut out log info on run time
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Pyhisics Engine Simulator");

    Camera2D camera = { 0 };
    init_camera(&camera);
    rigid_body* body_list = malloc(sizeof(rigid_body)*body_count);
    init_bodies(body_list, body_count);

    SetTargetFPS(framerate);                   // Set to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update values of drawables
        //----------------------------------------------------------------------------------
        // camera update
        input_camera(&camera);
        if (IsWindowResized() && !IsWindowFullscreen()) window(&camera);
        // player update
        vec d = {0,0};
        float dt = GetFrameTime();
        if (IsKeyDown(KEY_RIGHT))   d.x += speed * dt;
        if (IsKeyDown(KEY_LEFT))    d.x -= speed * dt;
        if (IsKeyDown(KEY_UP))      d.y += speed * dt;
        if (IsKeyDown(KEY_DOWN))    d.y -= speed * dt;
        if (IsKeyDown(KEY_F))       rotate(&body_list[0], PI / 2.f * dt);
        if (d.x != 0.0f || d.y != 0.0f) move(&body_list[0], d);
        // position update
        compute_position(body_list, body_count, GetFrameTime());
        //----------------------------------------------------------------------------------

        // Draw updated drawables
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // reset background color
            ClearBackground(BLACK);

            // drawing on camera
            BeginMode2D(camera);

                draw(&camera, body_list, body_count);
                // draw_with_sat_detection(&camera, body_list, body_count);

            EndMode2D();
            
            // extra
            draw_margins();
            draw_legend();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                      // Close window and OpenGL context
    for(int i=0; i<body_count; ++i){
        free(body_list[i].vertices.array);                          // Free allocated vertices
        free(body_list[i].transformed_vertices.array);    // ...
        free(body_list[i].triangles.array);                         // ...
    }
    free(body_list);                    // Free allocated bodies
    //--------------------------------------------------------------------------------------

    return;
}

Color RandomColor() {
    return (Color){
        .r = rand() % 256,
        .g = rand() % 256,
        .b = rand() % 256,
        .a = 255
    };
}

void init_camera(Camera2D* camera){
    // camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
    camera->target = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera->offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera->rotation = 0.0f;
    camera->zoom = 20.0f;
}

void init_bodies(rigid_body* body_list, int body_count) {

    vec pos = {0, 0};
    srand(time(NULL));

    for (int i = 0; i < body_count; ++i) {

        int n = rand() % 2;  // 0 = Circle, 1 = Box
        // int n = 1;
        pos.x = (float) (-10.0f + (float)(rand() % 30 + 1));
        pos.y = (float) (-10.0f + (float)(rand() % 30 + 1));

        Color randomColor = RandomColor();

        switch (n)
        {
        case Circle:
            init_circle_body(pos, 30, 30, 2, true, 1, randomColor, &body_list[i]);
            break;

        case Box:
            init_box_body(pos, 30, 30, 2, true, 2.0, 2.0, randomColor, &body_list[i]);
            break;
        }
        // printf("body: %d , posx: %f ,  posy: %f\n", i, body_list[i].position.x, body_list[i].position.y);
        // printf("%d %d\n", body_list[i].shape, i);

    }
}

void input_camera(Camera2D* camera){

    // Camera target follows player
    camera->target = (vec){0,0};
    // Uses log scaling to provide consistent zoom speed
    camera->zoom = expf(logf(camera->zoom) + ((float)GetMouseWheelMove()*0.1f));
    // Camera zoom controls
    // if (camera->zoom > 3.0f) camera->zoom = 3.0f;
    // else if (camera->zoom < 0.1f) camera->zoom = 0.1f;
    // Camera reset (zoom and rotation)
    if (IsKeyPressed(KEY_R))camera->zoom = 15.0f;
}

void window(Camera2D* camera){
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    camera->target = (vec){ screenWidth/2.0f, screenHeight/2.0f };
    camera->offset = (vec){ screenWidth/2.0f, screenHeight/2.0f };
}

void draw_margins(){
    DrawRectangle(0, 0, screenWidth, 5, BLUE);
    DrawRectangle(0, 5, 5, screenHeight - 10, BLUE);
    DrawRectangle(screenWidth - 5, 5, 5, screenHeight - 10, BLUE);
    DrawRectangle(0, screenHeight - 5, screenWidth, 5, BLUE);
}

void draw_legend(){
    DrawRectangle( 10, 10, 250, 113, Fade(LavanderBlue, 0.5f));
    DrawRectangleLines( 10, 10, 250, 113, LavanderBlue);
    DrawText("Free 2d camera controls:", 20, 20, 10, BLACK);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, BLACK);
    DrawText("- R to reset Zoom and Rotation", 40, 60, 10, BLACK);
    // DrawText("- A / S to Rotate", 40, 80, 10, BLACK);
    // DrawText("- Right/Left to move Offset", 40, 100, 10, BLACK);
}
