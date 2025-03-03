#ifndef MAPTILE_H
#define MAPTILE_H

#include "GameObject.h"
#include <raylib.h>

class MapTile : public GameObject {
public:
    Color color;
    bool hasTerrain;

    MapTile(Color c, bool hasTerrain, Vector2 position, Vector2 size);

    void Update() override;

    void Draw() override;

    void Destroy();
};

#endif
