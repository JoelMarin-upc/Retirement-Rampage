
#include "GameObject.cpp"
#include "MapTile.cpp"
#include <raylib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class MapReader : public GameObject {
private:
    string filePath;
	vector<vector<MapTile>> map;
    int screenX;
    int screenY;

public:
	MapReader(const string &filePath) : GameObject() {
        this->filePath = filePath;
	}

    void Init() override {
        LoadMap();
        Draw();
    }

    void LoadMap() {
        std::ifstream file(filePath);
        map = vector<vector<MapTile>>();

        screenX = GetScreenWidth();
        screenY = GetScreenHeight();

        if (!file.is_open()) return; 

        std::string line;
        int row = 0;
        int column = 0;
        while (std::getline(file, line)) {
            int size = ceil(screenX / line.size());
            std::vector<MapTile> rowTiles;
            for (char c : line) {
                Color color = Color();
                bool hasTerrain = true;
                switch (c)
                {
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
                Vector2 pos = Vector2();
                pos.x = column * size;
                pos.y = row * size;
                Vector2 sizeVector = Vector2();
                sizeVector.x = size;
                sizeVector.y = size;
                MapTile tile(color, hasTerrain, pos, sizeVector);
                rowTiles.push_back(tile);
                column++;
            }
            map.push_back(rowTiles);
            row++;
        }

        file.close();
        return;
    }

    void Update() override {

    }

    void Draw() {
        for (int x = 0; x < map.size(); x++) 
            for (int y = 0; y < map[x].size(); y++) 
                map[x][y].Draw();
    }

    void DestroyTiles() {

    }
};