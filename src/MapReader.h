#ifndef MAPREADER_H
#define MAPREADER_H

#include "GameObject.h"
#include "MapTile.h"
#include <string>
#include <vector>

class MapReader : public GameObject {
private:
    std::string filePath;
    std::vector<std::vector<MapTile>> map;
    std::vector<MapTile> optimizedTiles;
    bool shouldDraw;
    bool mapLoaded = false;

public:

    MapReader(const std::string& filePath);

    void Init() override;

    void LoadMap(bool optimize);

    void OptimizeTiles();

    void ChangeMap(std::string& path);

    void Update() override;
   
    void Draw();

    void DestroyTiles();

    std::vector<std::vector<MapTile>> GetMap() { return map; }
};

#endif
