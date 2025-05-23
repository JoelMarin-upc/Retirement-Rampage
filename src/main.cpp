#include "raylib.h"
#include "resource_dir.h"
#include "MapReader.h"
#include "GameObject.h"
#include "Player.h"
#include "TurnManager.h"
#include "Game.h"
#include "Theme.h"

#include <memory>
#include <vector>
#include <iostream>

int playerNum = 2;
double startTime = 0;
double playTime = 0;
bool playEnded = false;
bool playStarted = false;
bool playPaused = false;
float timePlayed;
Texture2D WORMS_logo;
Music music;
vector<string> maps;
vector<Theme> themes;
MapReader* mapReader;

int currentMap = 0;
int currentTheme = 0;

void InitPhase();
void UpdatingPhase();
void PaintingPhase();
void PaintEndScreen();
void PaintStartScreen();
void PaintPauseScreen();
void LoadMaps();
void LoadThemes();
void PrevMap();
void NextMap();
void PrevTheme();
void NextTheme();
void LoadGame();
void DrawCenteredText(const char* text, int x, int y, int fontSize, Color color);
void UpdatePlayerPositions();
Color GetRandomColor();

int main()
{

    SearchAndSetResourceDir("resources");

    SetTargetFPS(60);

    InitWindow(0, 0, "Worms");
    if (!IsWindowFullscreen()) ToggleFullscreen(); // Para debuggear comentar
    Game::screenWidth = GetScreenWidth();
    Game::screenHeight = GetScreenHeight();

    InitAudioDevice();

    LoadMaps();
    LoadThemes();
    LoadGame();

    InitPhase();
    while (!WindowShouldClose())
    {
        if (!playStarted) {
            PaintStartScreen();
            if (IsKeyReleased(KEY_RIGHT)) NextMap();
            if (IsKeyReleased(KEY_LEFT)) PrevMap();
            if (IsKeyReleased(KEY_UP)) PrevTheme();
            if (IsKeyReleased(KEY_DOWN)) NextTheme();
            Game::GetMap()->Draw();
            if (IsKeyReleased(KEY_ENTER)) playStarted = true;
            if (IsKeyReleased(KEY_ESCAPE)) break;
            startTime = GetTime();
            continue;
        }
        
        if (playPaused)
        {
            if (IsKeyReleased(KEY_P)) playPaused = false;
            if (IsKeyReleased(KEY_TAB)) LoadGame();
            if (IsKeyReleased(KEY_ESCAPE))  break;
        }
        else {
            if (IsKeyReleased(KEY_P)) playPaused = true;
            UpdatingPhase();
        }
        
        //music
        UpdateMusicStream(music); 
        timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music);
        if (timePlayed > 1.0f) timePlayed = 1.0f;

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
    
    UnloadMusicStream(music);
    CloseAudioDevice();
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
    ClearBackground(BLACK);
    for (const auto& gameObject : Game::gameObjects) {
        gameObject->Draw();
    }
    if (playPaused) PaintPauseScreen();
    EndDrawing();
}

void PaintStartScreen() {
    BeginDrawing();

    ClearBackground(SKYBLUE);

    DrawCenteredText("Trufa Edition", Game::screenWidth / 2, Game::screenHeight / 4, 100, RED);
    
    WORMS_logo = LoadTexture("WORMS_logo.png");
    DrawTexture(WORMS_logo, GetScreenWidth()/2-WORMS_logo.width/2,GetScreenHeight()/3/*750, 250,*/, WHITE);

    DrawCenteredText("Press [LEFT] and [RIGHT] to change map", Game::screenWidth / 2, Game::screenHeight / 2 + 40, 25, WHITE);
    DrawCenteredText("Press [UP] and [DOWN] to change theme", Game::screenWidth / 2, Game::screenHeight / 2 + 75, 25, WHITE);
    DrawCenteredText("Press [ENTER] to start", Game::screenWidth / 2, Game::screenHeight / 2 + 110, 25, WHITE);

    DrawText("Press [ESC] to exit", 30, Game::screenHeight - 50, 25, WHITE);

    DrawCenteredText("By Trufa Productions", Game::screenWidth - 180, Game::screenHeight - 40, 25, WHITE);

    EndDrawing();
}

void PaintEndScreen() {
    BeginDrawing();

    ClearBackground(SKYBLUE);
    Texture2D EndTexture;

    Player* winner = Game::winner;

    TurnManager* turnManager = Game::GetTurnManager();

    int turns = turnManager->turns;
    
    int minutes = static_cast<int>(playTime) / 60;
    int seconds = static_cast<int>(playTime) % 60;
    char timeText[20];
    snprintf(timeText, sizeof(timeText), "Time: %dm %ds", minutes, seconds);

    DrawCenteredText("Winner", Game::screenWidth / 2, Game::screenHeight / 2 - 45, 60, GREEN);

    DrawCenteredText(TextFormat("Player %02i", winner->playerNum), Game::screenWidth / 2, Game::screenHeight / 2, 40, GREEN);
    DrawCenteredText(timeText, Game::screenWidth / 2, Game::screenHeight / 2 + 60, 25, WHITE);
    DrawCenteredText(TextFormat("Turns: %01i", turns), Game::screenWidth / 2, Game::screenHeight / 2 + 80, 25, WHITE);
    
    DrawText("Press [ESC] to exit", 30, Game::screenHeight - 50, 25, WHITE);
    DrawCenteredText("Press [ENTER] to restart", Game::screenWidth - 200, Game::screenHeight - 40, 25, WHITE);

    EndDrawing();
}

void PaintPauseScreen() {
    DrawCenteredText("PAUSED", Game::screenWidth / 2, Game::screenHeight / 2 - 200, 60, WHITE);
    DrawCenteredText("Press [P] to resume", Game::screenWidth / 2, Game::screenHeight / 2, 25, WHITE);
    DrawCenteredText("Press [TAB] to return to menu", Game::screenWidth / 2, Game::screenHeight / 2 + 40, 25, WHITE);
    DrawCenteredText("Press [ESC] to exit game", Game::screenWidth / 2, Game::screenHeight / 2 + 80, 25, WHITE);
}

void LoadMaps() {
    maps = vector<string>();
    const char* path = "Maps/2players";
    FilePathList files = LoadDirectoryFiles(path);

    for (int i = 0; i < files.count; ++i) {
        const char* filePath = files.paths[i];
        std::string fileStr(filePath);
        if (fileStr.substr(fileStr.size() - 4) == ".png") maps.push_back(filePath);
    }

    UnloadDirectoryFiles(files);
}

void LoadThemes() {
    themes = vector<Theme>();
    const char* path = "Themes";
    FilePathList subdirs = LoadDirectoryFiles(path);

    for (int i = 0; i < subdirs.count; ++i) {
        const char* filePath = subdirs.paths[i];
        std::string fileStr(filePath);
        themes.push_back(Theme(fileStr));
    }

    UnloadDirectoryFiles(subdirs);
}

void PrevMap() {
    currentMap--;
    if (currentMap < 0) currentMap = maps.size() - 1;
    Game::GetMap()->ChangeMap(maps[currentMap], true);
    UpdatePlayerPositions();
}

void NextMap() {
    currentMap++;
    if (currentMap >= maps.size()) currentMap = 0;
    Game::GetMap()->ChangeMap(maps[currentMap], true);
    UpdatePlayerPositions();
}

void PrevTheme() {
    currentTheme--;
    if (currentTheme < 0) currentTheme = themes.size() - 1;
    Game::GetMap()->ChangeTheme(themes[currentTheme]);
}

void NextTheme() {
    currentTheme++;
    if (currentTheme >= themes.size()) currentTheme = 0;
    Game::GetMap()->ChangeTheme(themes[currentTheme]);
}

void LoadGame() {
    for (int i = 0; i < Game::gameObjects.size(); i++) Game::gameObjects[i].reset();
    Game::gameObjects = std::vector<std::unique_ptr<GameObject>>();
    Game::playerIndexes.clear();

    playPaused = false;
    playStarted = false;
    playEnded = false;
    Game::ended = false;
    Game::bottomY = Game::screenHeight;

    //SFX
    timePlayed = 0.0f;
    music = LoadMusicStream("01 the wormsong.mp3");
    PlayMusicStream(music);

    // MAPA
    std::unique_ptr<GameObject> map = std::make_unique<MapReader>();
    MapReader* mapObj = dynamic_cast<MapReader*>(map.get());
    mapObj->ChangeMap(maps[currentMap], true);
    mapObj->ChangeTheme(themes[currentTheme]);
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
            Game::AddPlayer(std::move(player));
        }
    }

    // TURN MANAGER 
    turnManagerObj->Start();
    Game::gameObjects.push_back(std::move(turnManager)); // Tiene que ser el ultimo game object en la lista
}

void UpdatePlayerPositions() {
    vector<MapTile> playerTiles = Game::GetMap()->GetPlayers();
    for (int i = 0; i < playerTiles.size(); i++) {
        if (playerTiles[i].tileChar == '1') {
            Vector2 pos = playerTiles[i].position;
            static_cast<Player*>(Game::gameObjects[Game::playerIndexes[i + 1]].get())->Move(pos, false);
        }
    }
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