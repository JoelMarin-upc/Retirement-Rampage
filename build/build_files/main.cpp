
#include "raylib.h"

#include "resource_dir.h"

#include "MapReader.h"

#include "GameObject.h"

#include <memory>

#include <vector>
#include <iostream>

std::vector<std::unique_ptr<GameObject>> gameObjects;

void InitPhase();
void UpdatingPhase();
void PaintingPhase();

int main()
{
	std::string mapName = "map1.txt";
	gameObjects = std::vector<std::unique_ptr<GameObject>>();
	SearchAndSetResourceDir("resources");
	std::string path = GetDirectoryPath(mapName.c_str());
	std::string fullPath = path + mapName;

	InitWindow(0, 0, "Game");
	std::unique_ptr<GameObject> map = std::make_unique<MapReader>(fullPath);
	gameObjects.push_back(std::move(map));

	InitPhase();
	while (!WindowShouldClose())
	{
		UpdatingPhase();
		PaintingPhase();
	}

	CloseWindow();
	return 0;
}

void InitPhase() {
	for (const auto& gameObject : gameObjects) {
		gameObject->Init();
	}
}

void UpdatingPhase() {
	for (const auto& gameObject : gameObjects) {
		gameObject->Update();
	}
}

void PaintingPhase() {
	BeginDrawing();
	for (const auto& gameObject : gameObjects) {
		gameObject->Draw();
	}
	EndDrawing();
}