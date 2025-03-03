#include "MapReader.h"
#include <cmath>
#include <fstream>
#include <raylib.h>
#include <iostream>

using namespace std;

MapReader::MapReader(const std::string& filePath) : GameObject() {
    this->filePath = filePath;
    shouldDraw = true;
}

void MapReader::Init() {
    LoadMap();
    Draw();
}

void MapReader::LoadMap() {
    std::ifstream file(filePath);
    map = std::vector<std::vector<MapTile>>();

    screenX = GetScreenWidth();
    screenY = GetScreenHeight();

    if (!file.is_open()) file.open(filePath);

    std::string line;
    //std::vector<>
    int row = 0;
    while (std::getline(file, line)) {
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

            int xPos = column * size;
            int yPos = screenY - size - row * size;
            Vector2 pos = { xPos, yPos };
            Vector2 sizeVector = { size, size };

            MapTile tile(color, hasTerrain, pos, sizeVector);
            rowTiles.push_back(tile);
            column++;
        }
        map.push_back(rowTiles);
        row++;
    }

    file.close();
}

void MapReader::Update() {
    //if (hit) shouldDraw = true;
}

void MapReader::Draw() {
    //if (!shouldDraw) return;
    for (int x = 0; x < map.size(); x++) {
        for (int y = 0; y < map[x].size(); y++) {
            map[x][y].Draw();
        }
    }
    shouldDraw = false;
}

void MapReader::DestroyTiles() {

}
