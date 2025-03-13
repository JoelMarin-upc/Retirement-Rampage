#include "raylib.h"
#include "resource_dir.h"
#include "MapReader.h"
#include "GameObject.h"
#include "Player.h"

#include <memory>
#include <vector>
#include <iostream>

static const int screenWidth = 800;
static const int screenHeight = 450;
//Vector2 playerSize = { 30,30 };
//Vector2 playerPosition = { screenWidth / 2, screenHeight / 2 };
//Vector2 centerPosition = { playerPosition.x + (playerSize.x / 2) - (playerAim.crosshairSize.x / 2) ,playerPosition.y + (playerSize.y / 2) - (playerAim.crosshairSize.x / 2) };

std::vector<std::unique_ptr<GameObject>> gameObjects;

void InitPhase();
void UpdatingPhase();
void PaintingPhase();

int main()
{
    gameObjects = std::vector<std::unique_ptr<GameObject>>();
    SearchAndSetResourceDir("resources");

    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "Game");

    // MAPA
    std::string mapName = "map1.txt";
    std::string path = GetDirectoryPath(mapName.c_str()) + mapName;
    std::unique_ptr<GameObject> map = std::make_unique<MapReader>(path);
    MapReader* mapObj = dynamic_cast<MapReader*>(map.get());
    mapObj->LoadMap(true);
    gameObjects.push_back(std::move(map));

    // PLAYER 1
    Vector2 size = { 30, 30 };
    Vector2 defPos = { 1, 1 };
    Vector2 pos = defPos;
    if (mapObj) {
        std::vector<std::vector<MapTile>> mapMatrix = mapObj->GetMap();
        for (int i = 0; i < mapMatrix.size() && pos.x == defPos.x && pos.y == defPos.y; i++)
            for (int j = 0; j < mapMatrix[i].size() && pos.x == defPos.x && pos.y == defPos.y; j++)
                if (mapMatrix[i][j].tileChar == '1')
                    pos = mapMatrix[i][j].position;
        if (pos.x != defPos.x || pos.y != defPos.y) {
            //pos.x -= size.x;
            pos.y -= size.y;
        }
    }
    std::unique_ptr<GameObject> player = std::make_unique<Player>(pos, size);
    gameObjects.push_back(std::move(player));

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
    ClearBackground(SKYBLUE);
    for (const auto& gameObject : gameObjects) {
        gameObject->Draw();
    }
    EndDrawing();
}