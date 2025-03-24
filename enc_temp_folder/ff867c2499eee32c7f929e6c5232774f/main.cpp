#include "raylib.h"
#include "resource_dir.h"
#include "MapReader.h"
#include "GameObject.h"
#include "Player.h"

#include <memory>
#include <vector>
#include <iostream>
#include "Game.h"

static const int screenWidth = 800;
static const int screenHeight = 450;

int playerNum = 2;
std::vector<Player*>playerList(playerNum);
int currentPlayer = 0;



//Vector2 playerSize = { 30,30 };
//Vector2 playerPosition = { screenWidth / 2, screenHeight / 2 };
//Vector2 centerPosition = { playerPosition.x + (playerSize.x / 2) - (playerAim.crosshairSize.x / 2) ,playerPosition.y + (playerSize.y / 2) - (playerAim.crosshairSize.x / 2) };

void InitPhase();
void UpdatingPhase();
void PaintingPhase();
void CheckTurn();

int main()
{
    Game::gameObjects = std::vector<std::unique_ptr<GameObject>>();
    SearchAndSetResourceDir("resources");

    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "Game");

    // MAPA
    std::string mapName = "map2.txt";
    std::string path = GetDirectoryPath(mapName.c_str()) + mapName;
    std::unique_ptr<GameObject> map = std::make_unique<MapReader>(path);
    MapReader* mapObj = dynamic_cast<MapReader*>(map.get());
    mapObj->LoadMap(true);
    Game::gameObjects.push_back(std::move(map)); // Tiene que ser el 1r game object en la lista

    // PLAYER 1
        

        Vector2 size = { 30, 30 };
        Vector2 defPos = { 1, 1 };
        Vector2 pos = defPos;
        for (MapTile& tile : mapObj->GetPlayers()) {
            if (tile.tileChar == '1') {
                pos = tile.position;
                if (pos.x != defPos.x || pos.y != defPos.y) pos.y -= size.y;
                std::unique_ptr<GameObject> player = std::make_unique<Player>(pos, size);
                playerList[currentPlayer] = static_cast<Player*>(player.get());
                Game::gameObjects.push_back(std::move(player));               
                ++currentPlayer;
            }
        }
        currentPlayer = 0;
        playerList[currentPlayer]->isTurn=true;
        playerList[currentPlayer]->playerAim.isTurn = true;
            
        
       

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
    CheckTurn();
}


void CheckTurn() {
    if (playerList[currentPlayer]->isTurn == false) {
        if (currentPlayer < (playerNum - 1)) ++currentPlayer;
        else currentPlayer = 0;
        playerList[currentPlayer]->isTurn = true;
        playerList[currentPlayer]->playerAim.isTurn = true;
        std::cout << currentPlayer;
    }
}


void PaintingPhase() {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    std::string s = std::to_string(currentPlayer + 1);
    const char* cstr = s.c_str();
    DrawText("player", 300, 20, 20, BLACK);
    DrawText(cstr, 370, 20, 20, BLACK);
    for (const auto& gameObject : Game::gameObjects) {
        gameObject->Draw();
    }
    EndDrawing();
}