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
const int body_count = 10;
/*******************************************************************************************/

void PhysicsEngineRun()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    SetTraceLogLevel(LOG_ERROR);        // Cut out log info on run time
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Pyhisics Engine Simulator");

    Camera2D camera = { 0 };
    init_camera(&camera);
    rigid_body* body_list = malloc(sizeof(rigid_body)*body_count);
    init_bodies(body_list, body_count);

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update values of drawables
        //----------------------------------------------------------------------------------
        input_camera(&camera);
        if (IsWindowResized() && !IsWindowFullscreen()) window(&camera);
        // Player movement
        if (IsKeyDown(KEY_RIGHT)) body_list[0].position.x += 0.5;
        else if (IsKeyDown(KEY_LEFT)) body_list[0].position.x -= 0.5;
        else if (IsKeyDown(KEY_UP)) body_list[0].position.y -= 0.5;
        else if (IsKeyDown(KEY_DOWN)) body_list[0].position.y += 0.5;
        //----------------------------------------------------------------------------------

        // Draw updated drawables
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // reset background color
            ClearBackground(RoyaleBlue);

            // drawing on camera
            BeginMode2D(camera);

                draw(&camera, body_list, body_count);
                // DrawCircle(0,0,1,WHITE);

            EndMode2D();
            
            // extra
            draw_margins();
            draw_legend();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
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
    camera->zoom = 15.0f;
}

void init_bodies(rigid_body* body_list, int body_count) {

    vec pos = {0, 0};
    srand(time(NULL));

    for (int i = 0; i < body_count; ++i) {

        int n = rand() % 1;  // 0 = Circle, 1 = Box
        pos.x = -10.0 + (float)(rand() % 30 + 1);
        pos.y = -10.0 + (float)(rand() % 30 + 1);

        Color randomColor = RandomColor();

        switch (n)
        {
        case Circle:
            init_circle_body(pos, 30, 30, 2, true, 2, randomColor, &body_list[i]);
            break;

        case Box:
            init_box_body(pos, 30, 30, 2, true, 10.0, 20.0, randomColor, &body_list[i]);
            break;
        }
    }
}

void input_camera(Camera2D* camera){

    // Camera target follows player
    camera->target = (Vector2){0,0};
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
    camera->target = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera->offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
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
