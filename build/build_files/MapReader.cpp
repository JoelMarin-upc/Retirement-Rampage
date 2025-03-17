#include "MapReader.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

MapReader::MapReader(const std::string& filePath) : GameObject() {
    this->filePath = filePath;
}

void MapReader::Init() {
    if (!mapLoaded) LoadMap(true);
}

Color GetRandomColor() {
    return {
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            255
    };
}

void MapReader::LoadMap(bool optimize) {
    std::ifstream file(filePath);
    map = std::vector<std::vector<MapTile>>();

    int screenX = GetScreenWidth();
    int screenY = GetScreenHeight();

    if (!file.is_open()) file.open(filePath);

    std::string line;
    std::vector<string> lines;
    while (std::getline(file, line)) lines.push_back(line);
    int row = 0;
    std::reverse(lines.begin(), lines.end());
    for (string line : lines) {
        int column = 0;
        int size = std::ceil(screenX / line.size());  
        std::vector<MapTile> rowTiles;
        for (char c : line) {
            Color color = Color();
            bool hasTerrain = true;

            switch (c) {
            case 'D': // Dirt
                color.r = 140;
                color.g = 70;
                color.b = 0;
                color.a = 255;
                break;
            case 'G': // Grass
                color.r = 0;
                color.g = 140;
                color.b = 0;
                color.a = 255;
                break;
            default: // Nothing
                hasTerrain = false;
                break;
            }
            //color = GetRandomColor(); // TESTING
            int xPos = column * size;
            int yPos = screenY - size - row * size;
            Vector2 pos = { xPos, yPos };
            Vector2 sizeVector = { size, size };

            MapTile tile(color, hasTerrain, c, pos, sizeVector);
            rowTiles.push_back(tile);
            column++;

            if (c != '0' && isdigit(c)) {
                playerPositions.push_back(tile);
            }
        }
        map.push_back(rowTiles);
        row++;
    }

    file.close();
    if (optimize) OptimizeTiles();
    mapLoaded = true;
}

void MapReader::OptimizeTiles() {
    int rows = map.size();
    int cols = map[0].size();
    std::vector<MapTile> optimizedTiles;

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (!map[y][x].hasTerrain || visited[y][x]) continue;

            Color color = map[y][x].color;
            char tileType = map[y][x].tileChar;
            Vector2 position = map[y][x].position;
            unsigned int tileSize = map[y][x].size.x;
            int maxWidth = 0, maxHeight = 0;

            for (int w = x; w < cols && map[y][w].tileChar == tileType && !visited[y][w]; ++w) maxWidth++;

            bool canExpand = true;
            while (canExpand && (y + maxHeight < rows)) {
                for (int w = 0; w < maxWidth; ++w) {
                    if (map[y + maxHeight][x + w].tileChar != tileType || visited[y + maxHeight][x + w]) {
                        canExpand = false;
                        position.y = map[y + maxHeight][x + w].position.y;
                        break;
                    }
                }
                if (canExpand) maxHeight++;
            }

            for (int dy = 0; dy < maxHeight; ++dy)
                for (int dx = 0; dx < maxWidth; ++dx)
                    visited[y + dy][x + dx] = true;

            Vector2 size = { maxWidth * tileSize, maxHeight * tileSize };
            MapTile newTile(color, true, tileType, position, size);
            optimizedTiles.push_back(newTile);
        }
    }

    this->optimizedTiles = optimizedTiles;
}

void MapReader::ChangeMap(std::string& path) {
    filePath = path;
}

void MapReader::Update() {

}

void MapReader::Draw() {
    
    //DRAW UNOPTIMIZED TILES
    /*for (int x = 0; x < map.size(); x++) {
        for (int y = 0; y < map[x].size(); y++) {
            map[x][y].Draw();
        }
    }*/

    for (MapTile tile : optimizedTiles) tile.Draw();
}

bool IsFullCollision(Explosion exp, MapTile tile) {
    float distance = abs(Vector2Distance(exp.position, tile.GetCenter()));
    return distance >= exp.radius + tile.size.x;
}

void MapReader::DestroyTiles(Explosion exp) {
    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[i].size(); j++)
            if (CheckCollisionCircleRec(exp.position, exp.radius, map[i][j].GetRectangle()) /*&& IsFullCollision(exp, map[i][j])*/)
                map[i][j].Destroy();
    OptimizeTiles();
}