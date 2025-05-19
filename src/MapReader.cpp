#include "MapReader.h"
#include "raylib.h"
#include <Game.h>

using namespace std;

void MapReader::Init() {
    if (!mapLoaded) LoadMap(true);
}

Color GetRandColor() {
    return {
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            255
    };
}

void MapReader::LoadMap(bool optimize) {
    map = std::vector<std::vector<MapTile>>();
    playerPositions.clear();

    int screenX = GetScreenWidth();
    int screenY = GetScreenHeight();
    float size = Game::tileSize;

    std::vector<std::vector<char>> pixels = ReadImage(filePath.c_str());

    for (int row = 0; row < pixels.size(); row++) {
        //int size = std::ceil(screenX / pixels[row].size());
        std::vector<MapTile> rowTiles;
        for (int column = 0; column < pixels[row].size(); column++) {
            Color color = Color();
            bool hasTerrain = true;

            char c = pixels[row][column];
            if (c == DIRT) color = theme.dirtTile;
            else hasTerrain = false;
            
            //color = GetRandColor(); // TESTING
            int xPos = column * size;
            int yPos = row * size; //screenY - size - row * size;
            Vector2 pos = { xPos, yPos };
            Vector2 sizeVector = { size, size };

            MapTile tile(color, hasTerrain, c, pos, sizeVector);

            bool tileExists = false;
            for (auto& existingTile : rowTiles) {
                if (existingTile.position.x == tile.position.x && existingTile.position.y == tile.position.y) {
                    if (c == PLAYER) existingTile = tile;
                    tileExists = true;
                    break;
                }
            }

            if (!tileExists) rowTiles.push_back(tile);

            if (c == PLAYER) playerPositions.push_back(tile);
        }
        map.push_back(rowTiles);
    }

    AddGrass();
    if (optimize) OptimizeTiles();
    mapLoaded = true;
}

std::vector<std::vector<char>> MapReader::ReadImage(const char* img) {
    Image image = LoadImage(img);
    Color* colors = LoadImageColors(image);

    int width = image.width;
    int height = image.height;

    std::vector<std::vector<char>> pixels = std::vector<std::vector<char>>();
    for (int y = 0; y < height; ++y) {
        pixels.push_back(std::vector<char>());
        for (int x = 0; x < width; ++x) {
            int index = (y * width) + x;
            Color pixel = colors[index];
            char c = EMPTY;
            if (pixel.r == 255 && pixel.g == 0 && pixel.b == 0) c = PLAYER;
            if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) c = DIRT;
            pixels[y].push_back(c);
        }
    }

    UnloadImageColors(colors);
    UnloadImage(image);
    return pixels;
}

void MapReader::OptimizeTiles() {
    int rows = map.size();
    int cols = map[0].size();
    std::vector<MapTile> optimizedTiles;

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (visited[y][x] || !map[y][x].hasTerrain) continue;

            Color color = map[y][x].color;
            char tileType = map[y][x].tileChar;
            Vector2 position = map[y][x].position;
            unsigned int tileSize = map[y][x].size.x;

            int maxWidth = 0;
            while (x + maxWidth < cols && map[y][x + maxWidth].tileChar == tileType && !visited[y][x + maxWidth]) {
                maxWidth++;
            }

            int maxHeight = 0;
            bool canExpandVertically = true;
            while (canExpandVertically && (y + maxHeight < rows)) {
                for (int w = 0; w < maxWidth; ++w) {
                    if (map[y + maxHeight][x + w].tileChar != tileType || visited[y + maxHeight][x + w]) {
                        canExpandVertically = false;
                        break;
                    }
                }
                if (canExpandVertically) {
                    maxHeight++;
                }
            }

            for (int dy = 0; dy < maxHeight; ++dy) {
                for (int dx = 0; dx < maxWidth; ++dx) {
                    visited[y + dy][x + dx] = true;
                }
            }

            Vector2 newPosition = { x * tileSize, y * tileSize };
            Vector2 size = { maxWidth * tileSize, maxHeight * tileSize };
            MapTile newTile(color, true, tileType, newPosition, size);
            optimizedTiles.push_back(newTile);
        }
    }

    this->optimizedTiles = optimizedTiles;
}

void MapReader::AddGrass() {
    for (int col = 0; col < map[0].size(); col++) {
        for (int row = 0; row < map.size(); row++) {
            if (map[row][col].hasTerrain &&
               ((row > 0 && !map[row - 1][col].hasTerrain) || 
                (row > 1 && !map[row - 2][col].hasTerrain) || 
                (row > 2 && !map[row - 3][col].hasTerrain)))
            {
                map[row][col].tileChar = GRASS;
                map[row][col].color = theme.grassTile;
            }
        }
    }
}

void MapReader::ChangeMap(std::string path, bool optimize) {
    filePath = path;
    LoadMap(optimize);
}

void MapReader::ChangeTheme(Theme theme) {
    MapReader::theme = theme;
    LoadMap(true);
}

void MapReader::Update() {

}

void MapReader::Draw() {
    if (!shouldDraw) return;
    //DRAW UNOPTIMIZED TILES
    /*for (int x = 0; x < map.size(); x++) {
        for (int y = 0; y < map[x].size(); y++) {
            map[x][y].Draw();
        }
    }*/
    theme.DrawBackground();
    for (MapTile tile : optimizedTiles) tile.Draw();
}

void MapReader::DestroyTiles(Explosion exp) {
    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[i].size(); j++)
            if (CheckCollisionCircleRec(exp.position, exp.radius, map[i][j].GetRectangle()))
                map[i][j].Destroy();
    OptimizeTiles();
}