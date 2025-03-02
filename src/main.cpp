/*******************************************************************************************
*
*   raylib - classic game: gorilas
*
*   Sample game developed by Marc Palau and Ramon Santamaria
*
*   This game has been created using raylib v1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
//#define MAX_BUILDINGS                    15
//#define MAX_EXPLOSIONS                  200
#define MAX_PLAYERS                       1

//#define BUILDING_RELATIVE_ERROR          30        // Building size random range %
//#define BUILDING_MIN_RELATIVE_HEIGHT     20        // Minimum height in % of the screenHeight
//#define BUILDING_MAX_RELATIVE_HEIGHT     60        // Maximum height in % of the screenHeight
//#define BUILDING_MIN_GRAYSCALE_COLOR    120        // Minimum gray color for the buildings
//#define BUILDING_MAX_GRAYSCALE_COLOR    200        // Maximum gray color for the buildings

#define MIN_PLAYER_POSITION               5        // Minimum x position %
#define MAX_PLAYER_POSITION              20        // Maximum x position %

#define GRAVITY                       9.81f
#define DELTA_FPS                        60

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------



//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;




Vector2 position = { screenWidth / 2, screenHeight / 2 };
Vector2 aimingPoint;
Vector2 vectorDirector = { 1,0 };
float range = 100;
bool facingRight = true;
float angle = 0;


//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

// Additional module functions
static void InitPlayers(void);
static bool UpdatePlayer();

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "classic game: gorilas");

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

    if (!gameOver)
    {

        DrawRectangle(position.x, position.y, 5,5, BLUE);
       
        if (facingRight) DrawRectangle(aimingPoint.x, aimingPoint.y, 10,10, BLACK);
        else DrawRectangle(aimingPoint.x, aimingPoint.y, 10, 10, BLACK);
        
         
        if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    }
    else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

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

//--------------------------------------------------------------------------------------
// Additional module functions
//--------------------------------------------------------------------------------------


static void InitPlayers(void)
{
   
        aimingPoint = position;
       
}

static bool UpdatePlayer()
{

        // Left team
       // {
            // Distance (calculating the fire power)
            //player[playerTurn].aimingPower = sqrt(pow(position.x - GetMousePosition().x, 2) + pow(position.y - GetMousePosition().y, 2));
            // Calculates the angle via arcsin
            //player[playerTurn].aimingAngle = asin((position.y - GetMousePosition().y) / player[playerTurn].aimingPower) * RAD2DEG;
            // Point of the screen we are aiming at



    if (IsKeyDown(KEY_RIGHT)) {
        facingRight = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        facingRight = false;
    }
    if (IsKeyDown(KEY_UP) && (vectorDirector.x > 0 || vectorDirector.y > 0)) {
        angle -= 0.025;
        vectorDirector.y=sin(angle);
            //if (vectorDirector.y > 0) vectorDirector.x += 0.01;
           // else if (vectorDirector.y < 0) vectorDirector.x -= 0.01;
            //else vectorDirector.x -= 0.01;
        vectorDirector.x = cos(angle);
                //sqrt(1 - pow(vectorDirector.y, 2));
        }
        if (IsKeyDown(KEY_DOWN) && (vectorDirector.x > 0 || vectorDirector.y < 0)) {
            angle += 0.025;
            vectorDirector.y = sin(angle);
            vectorDirector.x = cos(angle);
            
            
            
        }
        

        if (facingRight) aimingPoint = { position.x + (vectorDirector.x * range) , position.y + (vectorDirector.y * range) };
        else  aimingPoint = { position.x - (vectorDirector.x * range) , position.y + (vectorDirector.y * range) };

            // Ball fired
            //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
          //  {
             //   player[playerTurn].previousPoint = aimingPoint;
              //  player[playerTurn].previousPower = player[playerTurn].aimingPower;
              //  player[playerTurn].previousAngle = player[playerTurn].aimingAngle;
                //ball.position = player[playerTurn].position;

              //  return true;
            //}


    return false;
}

