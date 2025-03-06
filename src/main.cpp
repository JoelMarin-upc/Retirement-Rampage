
#include "raylib.h"
#include <math.h>

#include "Aim.cpp"
#include "Launcher.cpp"

//#define GRAVITY                       9.81f
//#define DELTA_FPS                        60


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
        playerLauncher.Charging();
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

int main ()
{

	InitWindow(0, 0, "Game");
	MapReader
	while (!WindowShouldClose())
	{
		if () {
			paint();
		}
	}

	// Tell the window to use vysnc and work on high DPI displays
	//SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	//// Create the window and OpenGL context
	//InitWindow(1280, 800, "Hello Raylib");

	//// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	//SearchAndSetResourceDir("resources");

	//// Load a texture from the resources directory
	//Texture wabbit = LoadTexture("wabbit_alpha.png");
	//
	//// game loop
	//while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	//{
	//	// drawing
	//	BeginDrawing();

	//	// Setup the backbuffer for drawing (clear color and depth buffers)
	//	ClearBackground(BLACK);

	//	// draw some text using the default font
	//	DrawText("Hello Raylib", 200,200,20,WHITE);

	//	// draw our texture to the screen
	//	DrawTexture(wabbit, 400, 200, WHITE);
	//	
	//	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	//	EndDrawing();
	//}

	//// cleanup
	//// unload our texture so it can be cleaned up
	//UnloadTexture(wabbit);

	//// destory the window and cleanup the OpenGL context
	//CloseWindow();
	return 0;
}

void paint() {
	Color colorBack = WHITE;
	Color tankColor = RED;
	Color boxColor = BLUE;
	int tankX = 16;
	int tankY = 16;
	int boxesX = 300;
	int screenX = GetScreenWidth();
	int screenY = GetScreenHeight();
	int boxDim = screenX / boxesX;
	int boxesY = screenY / 2 / boxDim;

	BeginDrawing();
	ClearBackground(colorBack);
	for (int x = 0; x < boxesX; x++)
	{
		for (int y = 0; y < boxesY; y++)
		{
			int posX = screenX - (x * boxDim);
			int posY = screenY - (y * boxDim);
			DrawRectangle(posX, posY, boxDim, boxDim, boxColor);
		}
	}
	int tank1PosX = screenX - (boxDim * 10);
	int tank2PosX = screenX - (boxDim * (boxesX - 10));
	int tankPosY = screenY - (boxDim * boxesY + 1);
	DrawRectangle(tank1PosX, tankPosY, tankX, tankY, tankColor);
	DrawRectangle(tank2PosX, tankPosY, tankX, tankY, tankColor);
	EndDrawing();
}