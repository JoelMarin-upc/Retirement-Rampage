#ifndef MAPREADER_H
#define MAPREADER_H

#include "GameObject.h"
#include "MapTile.h"
#include "Explosion.h"
#include <string>
#include <vector>

class MapReader : public GameObject {
private:
    std::string filePath = "";
    std::vector<std::vector<MapTile>> map;
    std::vector<MapTile> optimizedTiles;
    std::vector<MapTile> playerPositions;
    bool mapLoaded = false;
    const char DIRT = 'D';
    const char GRASS = 'G';
    const char PLAYER = '1';
    const char EMPTY = '0';
    const Color DIRT_COLOR = { 140, 70, 0, 255 };
    const Color GRASS_COLOR = { 0, 140, 0, 255 };

public:
    bool shouldDraw = true;

    MapReader() : GameObject() { }

    void Init() override;

    std::vector<std::vector<char>> ReadImage(const char* img);

    void LoadMap(bool optimize);

    void OptimizeTiles();

    void AddGrass();

    void ChangeMap(std::string path, bool optimize);

    void Update() override;
   
    void Draw() override;

    void DestroyTiles(Explosion exp);

    std::vector<std::vector<MapTile>> GetMap() { return map; }

    std::vector<MapTile> GetOptimizedMap() { return optimizedTiles; }
    
    std::vector<MapTile> GetPlayers() { return playerPositions; }
};

#endif
