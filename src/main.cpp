#include "raylib.h"
#include "resource_dir.h"
#include "MapReader.h"
#include "GameObject.h"
#include "Player.h"
#include "TurnManager.h"
#include "Game.h"

#include <memory>
#include <vector>
#include <iostream>

static const int screenWidth = 800;
static const int screenHeight = 450;

//static const int screenWidth = GetScreenWidth();
//static const int screenHeight = GetScreenHeight();

int playerNum = 2;

//Vector2 playerSize = { 30,30 };
//Vector2 playerPosition = { screenWidth / 2, screenHeight / 2 };
//Vector2 centerPosition = { playerPosition.x + (playerSize.x / 2) - (playerAim.crosshairSize.x / 2) ,playerPosition.y + (playerSize.y / 2) - (playerAim.crosshairSize.x / 2) };


void InitPhase();
void UpdatingPhase();
void PaintingPhase();

int main()
{
    Game::gameObjects = std::vector<std::unique_ptr<GameObject>>();

    SearchAndSetResourceDir("resources");

    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "Game");
    Game::bottomY = screenHeight;

    // MAPA
    std::string mapName = "map2.txt";
    std::string path = GetDirectoryPath(mapName.c_str()) + mapName;
    std::unique_ptr<GameObject> map = std::make_unique<MapReader>(path);
    MapReader* mapObj = dynamic_cast<MapReader*>(map.get());
    mapObj->LoadMap(true);
    Game::gameObjects.push_back(std::move(map)); // Tiene que ser el 1r game object en la lista


    // PLAYERS
    std::unique_ptr<GameObject> turnManager = std::make_unique<TurnManager>(playerNum);
    TurnManager* turnManagerObj = dynamic_cast<TurnManager*>(turnManager.get());
    Vector2 size = { 30, 30 };
    Vector2 defPos = { 1, 1 };
    Vector2 pos = defPos;
    for (MapTile& tile : mapObj->GetPlayers()) {
        if (tile.tileChar == '1') {
            pos = tile.position;
            if (pos.x != defPos.x || pos.y != defPos.y) pos.y -= size.y;
            std::unique_ptr<GameObject> player = std::make_unique<Player>(turnManagerObj->currentPlayer + 1, pos, size);
            turnManagerObj->AddPlayer(static_cast<Player*>(player.get()));
            Game::gameObjects.push_back(std::move(player));               
        }
    }

    // TURN MANAGER 
    turnManagerObj->Start();
    Game::gameObjects.push_back(std::move(turnManager)); // Tiene que ser el ultimo game object en la lista

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
    for (const auto& gameObject : Game::gameObjects) {
        gameObject->Init();
    }
}

void UpdatingPhase() {
    for (const auto& gameObject : Game::gameObjects) {
        gameObject->Update(); 
    }
}

void PaintingPhase() {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    for (const auto& gameObject : Game::gameObjects) {
        gameObject->Draw();
    }
    EndDrawing();
}