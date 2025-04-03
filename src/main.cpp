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

int playerNum = 2;
double startTime = 0;
double playTime = 0;
bool playEnded = false;
bool playStarted = false;

//Vector2 playerSize = { 30,30 };
//Vector2 playerPosition = { screenWidth / 2, screenHeight / 2 };
//Vector2 centerPosition = { playerPosition.x + (playerSize.x / 2) - (playerAim.crosshairSize.x / 2) ,playerPosition.y + (playerSize.y / 2) - (playerAim.crosshairSize.x / 2) };


void InitPhase();
void UpdatingPhase();
void PaintingPhase();
void PaintEndScreen();
void PaintStartScreen();
void LoadGame();
void DrawCenteredText(const char* text, int x, int y, int fontSize, Color color);
Color GetRandomColor();

int main()
{
    SearchAndSetResourceDir("resources");

    SetTargetFPS(60);

    InitWindow(0, 0, "Game");
    if (!IsWindowFullscreen()) ToggleFullscreen();
    
    LoadGame();

    InitPhase();
    while (!WindowShouldClose())
    {
        if (!playStarted) {
            PaintStartScreen();
            if (IsKeyReleased(KEY_ENTER)) playStarted = true;
            if (IsKeyReleased(KEY_ESCAPE)) break;
            startTime = GetTime();
            continue;
        }
        UpdatingPhase();
        Game::CheckEndGame();
        if (Game::ended)
        {
            if (!playEnded) {
                playEnded = true;
                playTime = GetTime() - startTime;
            }
            PaintEndScreen();
            if (IsKeyReleased(KEY_ENTER)) LoadGame();
            if (IsKeyReleased(KEY_ESCAPE)) break;
        }
        else PaintingPhase();
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

void PaintStartScreen() {
    BeginDrawing();

    ClearBackground(SKYBLUE);

    DrawCenteredText("WORMS", Game::screenWidth / 2, Game::screenHeight / 3, 60, RED);

    DrawCenteredText("Press [ENTER] to start", Game::screenWidth / 2, Game::screenHeight / 2, 25, BLACK);

    DrawText("Press [ESC] to exit", 30, Game::screenHeight - 50, 25, BLACK);

    DrawCenteredText("By Trufa Productions", Game::screenWidth - 180, Game::screenHeight - 40, 25, BLACK);

    EndDrawing();
}

void PaintEndScreen() {
    BeginDrawing();

    ClearBackground(SKYBLUE);

    Player* winner = Game::winner;

    TurnManager* turnManager = Game::GetTurnManager();

    int turns = turnManager->turns;
    
    int minutes = static_cast<int>(playTime) / 60;
    int seconds = static_cast<int>(playTime) % 60;
    char timeText[20];
    snprintf(timeText, sizeof(timeText), "Time: %dm %ds", minutes, seconds);

    DrawCenteredText("Winner", Game::screenWidth / 2, Game::screenHeight / 2 - 45, 60, GREEN);

    DrawCenteredText(TextFormat("Player %02i", winner->playerNum), Game::screenWidth / 2, Game::screenHeight / 2, 40, GREEN);
    DrawCenteredText(timeText, Game::screenWidth / 2, Game::screenHeight / 2 + 60, 25, BLACK);
    DrawCenteredText(TextFormat("Turns: %01i", turns), Game::screenWidth / 2, Game::screenHeight / 2 + 80, 25, BLACK);
    
    DrawText("Press [ESC] to exit", 30, Game::screenHeight - 50, 25, BLACK);
    DrawCenteredText("Press [ENTER] to restart", Game::screenWidth - 200, Game::screenHeight - 40, 25, BLACK);

    EndDrawing();
}

void LoadGame() {
    Game::screenWidth = GetScreenWidth();
    Game::screenHeight = GetScreenHeight();

    for (int i = 0; i < Game::gameObjects.size(); i++) Game::gameObjects[i].reset();
    Game::gameObjects = std::vector<std::unique_ptr<GameObject>>();

    playStarted = false;
    playEnded = false;
    Game::ended = false;
    Game::bottomY = Game::screenHeight;

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
}

void DrawCenteredText(const char* text, int x, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;
    DrawText(text, x - textWidth / 2, y - textHeight / 2, fontSize, color);
}

Color GetRandomColor() {
    return {
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            255
    };
}