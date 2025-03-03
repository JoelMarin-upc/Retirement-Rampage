
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif


#define GRAVITY                       9.81f
#define DELTA_FPS                        60


static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;

Vector2 playerSize = { 30,30 };
Vector2 bulletSize = { 10,10 };
Vector2 position = { screenWidth / 2, screenHeight / 2 };
Vector2 centerPosition = { position.x + (playerSize.x / 2) - (bulletSize.x/2) ,position.y + (playerSize.y / 2) - (bulletSize.x / 2) };
Vector2 aimingPoint;
Vector2 vectorDirector = { 1,0 };
float range = 100;
bool facingRight = true;
float angle = 0;



static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

// Additional module functions
static void InitPlayers(void);
static bool UpdatePlayer();


int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "worms");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void)
{
    InitPlayers();
}
    
// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {
        UpdatePlayer();
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawRectangle(position.x, position.y, playerSize.x, playerSize.y, BLUE);

    if (facingRight) DrawRectangle(aimingPoint.x, aimingPoint.y, 10,10, BLACK);
    else DrawRectangle(aimingPoint.x, aimingPoint.y, bulletSize.x, bulletSize.y, BLACK);

    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

static void InitPlayers(void)
{
         
}

static bool UpdatePlayer()
{
    if (IsKeyDown(KEY_RIGHT)) {
        facingRight = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        facingRight = false;
    }
    if (IsKeyDown(KEY_UP) && (vectorDirector.x > 0 || vectorDirector.y > 0)) {
        angle -= 0.025;
        vectorDirector.y=sin(angle); 
        vectorDirector.x = cos(angle);
    }
    if (IsKeyDown(KEY_DOWN) && (vectorDirector.x > 0 || vectorDirector.y < 0)) {
        angle += 0.025;
        vectorDirector.y = sin(angle);
        vectorDirector.x = cos(angle);       
        }

    if (facingRight) aimingPoint = { centerPosition.x + (vectorDirector.x * range) , centerPosition.y + (vectorDirector.y * range) };
    else  aimingPoint = { centerPosition.x - (vectorDirector.x * range) , centerPosition.y + (vectorDirector.y * range) };

    return false;
}

