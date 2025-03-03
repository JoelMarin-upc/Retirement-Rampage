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
    int screenX;
    int screenY;
    bool shouldDraw;

public:
    MapReader(const std::string& filePath);

    void Init() override;

    void LoadMap();

    void Update() override;
   
    void Draw();

    void DestroyTiles();
};

#endif
