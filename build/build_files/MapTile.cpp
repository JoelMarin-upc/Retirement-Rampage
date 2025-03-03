#include "MapTile.h"

MapTile::MapTile(Color c, bool hasTerrain, Vector2 position, Vector2 size)
    : GameObject(position, size), color(c), hasTerrain(hasTerrain) {
}

void MapTile::Update() {
}

void MapTile::Draw() {
    if (!hasTerrain) return;  
    DrawRectangle(position.x, position.y, size.x, size.y, color);
}

void MapTile::Destroy() {
    hasTerrain = false;
}
