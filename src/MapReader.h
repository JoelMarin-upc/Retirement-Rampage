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

public:
    bool shouldDraw = true;

    MapReader() : GameObject() { }

    void Init() override;

    void LoadMap(bool optimize);

    void OptimizeTiles();

    void ChangeMap(std::string path, bool optimize);

    void Update() override;
   
    void Draw() override;

    void DestroyTiles(Explosion exp);

    std::vector<std::vector<MapTile>> GetMap() { return map; }

    std::vector<MapTile> GetOptimizedMap() { return optimizedTiles; }
    
    std::vector<MapTile> GetPlayers() { return playerPositions; }
};

#endif
