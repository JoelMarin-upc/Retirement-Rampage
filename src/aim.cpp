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
#define MAX_BUILDINGS                    15
#define MAX_EXPLOSIONS                  200
#define MAX_PLAYERS                       1

#define BUILDING_RELATIVE_ERROR          30        // Building size random range %
#define BUILDING_MIN_RELATIVE_HEIGHT     20        // Minimum height in % of the screenHeight
#define BUILDING_MAX_RELATIVE_HEIGHT     60        // Maximum height in % of the screenHeight
#define BUILDING_MIN_GRAYSCALE_COLOR    120        // Minimum gray color for the buildings
#define BUILDING_MAX_GRAYSCALE_COLOR    200        // Maximum gray color for the buildings

#define MIN_PLAYER_POSITION               5        // Minimum x position %
#define MAX_PLAYER_POSITION              20        // Maximum x position %

#define GRAVITY                       9.81f
#define DELTA_FPS                        60

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct Player {
    Vector2 position;
    Vector2 size;

    Vector2 aimingPoint;
    int aimingAngle;
    int aimingPower;

    Vector2 previousPoint;
    int previousAngle;
    int previousPower;

    Vector2 impactPoint;

    bool isLeftTeam;                // This player belongs to the left or to the right team
    bool isPlayer;                  // If is a player or an AI
    bool isAlive;
} Player;




//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;

static Player player[MAX_PLAYERS] = { 0 };


static int playerTurn = 0;
static bool ballOnAir = false;

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
static bool UpdatePlayer(int playerTurn);

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
        UpdatePlayer(playerTurn);
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

        // Draw players
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (player[i].isAlive)
            {
                if (player[i].isLeftTeam) DrawRectangle(player[i].position.x - player[i].size.x / 2, player[i].position.y - player[i].size.y / 2,
                    player[i].size.x, player[i].size.y, BLUE);
                else DrawRectangle(player[i].position.x - player[i].size.x / 2, player[i].position.y - player[i].size.y / 2,
                    player[i].size.x, player[i].size.y, RED);
            }
        }

        
        // Draw the angle and the power of the aim, and the previous ones
        if (true)
        {
            // Draw shot information
            /*
            if (player[playerTurn].isLeftTeam)
            {
                DrawText(TextFormat("Previous Point %i, %i", (int)player[playerTurn].previousPoint.x, (int)player[playerTurn].previousPoint.y), 20, 20, 20, DARKBLUE);
                DrawText(TextFormat("Previous Angle %i", player[playerTurn].previousAngle), 20, 50, 20, DARKBLUE);
                DrawText(TextFormat("Previous Power %i", player[playerTurn].previousPower), 20, 80, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Point %i, %i", (int)player[playerTurn].aimingPoint.x, (int)player[playerTurn].aimingPoint.y), 20, 110, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Angle %i", player[playerTurn].aimingAngle), 20, 140, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Power %i", player[playerTurn].aimingPower), 20, 170, 20, DARKBLUE);
            }
            else
            {
                DrawText(TextFormat("Previous Point %i, %i", (int)player[playerTurn].previousPoint.x, (int)player[playerTurn].previousPoint.y), screenWidth*3/4, 20, 20, DARKBLUE);
                DrawText(TextFormat("Previous Angle %i", player[playerTurn].previousAngle), screenWidth*3/4, 50, 20, DARKBLUE);
                DrawText(TextFormat("Previous Power %i", player[playerTurn].previousPower), screenWidth*3/4, 80, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Point %i, %i", (int)player[playerTurn].aimingPoint.x, (int)player[playerTurn].aimingPoint.y), screenWidth*3/4, 110, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Angle %i", player[playerTurn].aimingAngle), screenWidth*3/4, 140, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Power %i", player[playerTurn].aimingPower), screenWidth*3/4, 170, 20, DARKBLUE);
            }
            */

            // Draw aim
            if (true)
            {
                // Previous aiming
              //  DrawTriangle((Vector2) ( (player[playerTurn].position.x - player[playerTurn].size.x / 4, player[playerTurn].position.y - player[playerTurn].size.y / 4),
             //       (Vector2) {
               //     player[playerTurn].position.x + player[playerTurn].size.x / 4, player[playerTurn].position.y + player[playerTurn].size.y / 4
              //  },
              //      player[playerTurn].previousPoint, GRAY);

                // Actual aiming

                Vector2 p1 = Vector2();
                p1.x = player[playerTurn].position.x - player[playerTurn].size.x / 4;
                p1.y = player[playerTurn].position.y - player[playerTurn].size.y / 4;
                
                Vector2 p2 = Vector2();
                p2.x = player[playerTurn].position.x + player[playerTurn].size.x / 4;
                p2.y = player[playerTurn].position.y + player[playerTurn].size.y / 4;

                Vector2 aim = player[playerTurn].aimingPoint;


                DrawTriangle( p1,p2,aim, BLACK);
            }
        }

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
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        player[i].isAlive = true;

        // Decide the team of this player
        if (i % 2 == 0) player[i].isLeftTeam = true;
        else player[i].isLeftTeam = false;

        // Now there is no AI
        player[i].isPlayer = true;

        // Set size, by default by now
        player[i].size = { 40, 40 };

        // Set position
        if (player[i].isLeftTeam) player[i].position.x = GetRandomValue(screenWidth * MIN_PLAYER_POSITION / 100, screenWidth * MAX_PLAYER_POSITION / 100);
        else player[i].position.x = screenWidth - GetRandomValue(screenWidth * MIN_PLAYER_POSITION / 100, screenWidth * MAX_PLAYER_POSITION / 100);

        
        player[i].position.x = player[i].position.x;
        player[i].position.y = screenHeight / 2;

        // Set statistics to 0
        player[i].aimingPoint = player[i].position;
        player[i].previousAngle = 0;
        player[i].previousPower = 0;
        player[i].previousPoint = player[i].position;
        player[i].aimingAngle = 0;
        player[i].aimingPower = 0;

        player[i].impactPoint = { -100, -100 };
    }
}

static bool UpdatePlayer()
{

        // Left team
       // {
            // Distance (calculating the fire power)
            player[playerTurn].aimingPower = sqrt(pow(player[playerTurn].position.x - GetMousePosition().x, 2) + pow(player[playerTurn].position.y - GetMousePosition().y, 2));
            // Calculates the angle via arcsin
            player[playerTurn].aimingAngle = asin((player[playerTurn].position.y - GetMousePosition().y) / player[playerTurn].aimingPower) * RAD2DEG;
            // Point of the screen we are aiming at
            player[playerTurn].aimingPoint = GetMousePosition();

            // Ball fired
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                player[playerTurn].previousPoint = player[playerTurn].aimingPoint;
                player[playerTurn].previousPower = player[playerTurn].aimingPower;
                player[playerTurn].previousAngle = player[playerTurn].aimingAngle;
                //ball.position = player[playerTurn].position;

                return true;
            }


    return false;
}

