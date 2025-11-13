#include "application.h"

/***************************************/

// window size
int screenWidth = 1280;
int screenHeight = 720;

// Blueprint Color Scheme
const Color RoyaleBlue = {48, 87, 225};
const Color LavanderBlue = {206, 216, 247};
const Color ResolutionBlue = {0, 32, 130};

/************************************* */

void draw_margins();
void draw_legend();

void PhysicsEngineRun()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Pyhisics Engine Simulator");

    Rectangle player = { 400, 280, 40, 40 };

    Camera2D camera = { 0 };
    // camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
    camera.target = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Player movement
        if (IsKeyDown(KEY_RIGHT)) player.x += 2;
        else if (IsKeyDown(KEY_LEFT)) player.x -= 2;

        // Camera target follows player
        camera.target = (Vector2){ player.x + 20, player.y + 20 };

        // Uses log scaling to provide consistent zoom speed
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f));
        
        // Camera zoom controls
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        // Camera reset (zoom and rotation)
        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RoyaleBlue);
            
            if (IsWindowResized() && !IsWindowFullscreen())
            {
                screenWidth = GetScreenWidth();
                screenHeight = GetScreenHeight();
                camera.target = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
                camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
            }

            // drawing on screen
            BeginMode2D(camera);

                DrawRectangleRec(player, RED);
                DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);

                DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, GREEN);
                DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, GREEN);

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
    DrawText("- Right/Left to move Offset", 40, 40, 10, BLACK);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, BLACK);
    DrawText("- A / S to Rotate", 40, 80, 10, BLACK);
    DrawText("- R to reset Zoom and Rotation", 40, 100, 10, BLACK);
}
