/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "MapReader.h"

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