
#include "raylib.h"

#include "resource_dir.h"

#include "MapReader.cpp"

vector<GameObject> gameObjects;

int main()
{
	gameObjects = vector<GameObject>();
	SearchAndSetResourceDir("resources");
	string path = GetDirectoryPath("mapa1.txt");

	InitWindow(0, 0, "Game");
	MapReader map(path);
	gameObjects.push_back(map);

	InitPhase();
	while (!WindowShouldClose())
	{
		UpdatingPhase();
		PaintingPhase();
	}

	CloseWindow();

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

static void InitPhase() {
	for (int i = 0; i < gameObjects.size(); i++) gameObjects[i].Init();
}

static void UpdatingPhase() {
	for (int i = 0; i < gameObjects.size(); i++) gameObjects[i].Update();
}

static void PaintingPhase() {
	BeginDrawing();
	for (int i = 0; i < gameObjects.size(); i++) gameObjects[i].Draw();
	EndDrawing();
}