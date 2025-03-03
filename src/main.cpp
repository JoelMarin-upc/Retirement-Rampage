
#include "raylib.h"
#include <math.h>

#include "Aim.cpp"
#include "Launcher.cpp"


#define GRAVITY                       9.81f
#define DELTA_FPS                        60


static const int screenWidth = 800;
static const int screenHeight = 450;

Aim playerAim;
Launcher playerLauncherEmpty;
Launcher playerLauncher;

bool aiming = true;
bool charging = false;

Vector2 playerSize = { 30,30 };
Vector2 position = { screenWidth / 2, screenHeight / 2 };

Vector2 centerPosition = { position.x + (playerSize.x / 2) - (playerAim.crosshairSize.x / 2) ,position.y + (playerSize.y / 2) - (playerAim.crosshairSize.x / 2)};


  
static void UpdateGame(void);       
static void DrawGame(void);               
static void UpdateDrawFrame(void); 


int main(void)
{
   
    InitWindow(screenWidth, screenHeight, "worms");

    SetTargetFPS(60);

    playerAim.InitAim(centerPosition);
    playerLauncherEmpty.InitLauncher(centerPosition);
    playerLauncher.InitLauncher(centerPosition);
   
    while (!WindowShouldClose())   
    {
        UpdateDrawFrame();
    }
    return 0;
}

void UpdateGame(void)
{
   // if (IsKeyPressed) playerLauncher = playerLauncherEmpty;
    if (IsKeyDown(KEY_SPACE)) {
        if (!charging) {
            aiming = true;
            charging = true;
            playerLauncher = playerLauncherEmpty;
        }
        if(playerAim.facingRight)  playerLauncher.Charging();
        else  playerLauncher.Charging();
    }

    if (IsKeyReleased(KEY_SPACE)) {
        aiming = false;
        charging = false;
        if(playerAim.facingRight)playerLauncher.InitialVelocity(playerAim.vectorDirector);
        else playerLauncher.InitialVelocity({-playerAim.vectorDirector.x, playerAim.vectorDirector.y});
    }
    //if (aiming) 
    if(!charging)playerAim.Update();
    if(!aiming) playerLauncher.Shoot();
      
}

void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    //drawPlayer
    DrawRectangle(position.x, position.y, playerSize.x, playerSize.y, BLUE);

    playerAim.Draw();

    EndDrawing();
}



void UpdateDrawFrame(void) 
{
    UpdateGame();
    DrawGame();
}

static void InitPlayers(void)
{
         
}

