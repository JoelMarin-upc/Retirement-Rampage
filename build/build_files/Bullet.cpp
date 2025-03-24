#include <raylib.h>
#include <vector>
#include "Bullet.h"
#include "Explosion.h"
#include "MapReader.h"
#include "Game.h"

void Bullet::Update() { 
    if (destroyed) { 
        explosion.Update(); 
        return; 
    }
    if (HasCollision()) Explode(); 
    else Shoot(); 
}

void Bullet::Charging() { velocityModule += velocityIncrease; }

void Bullet::Shoot() {
    actualVelocity.y += gravity;
    position.x += actualVelocity.x;
    position.y += actualVelocity.y;
}

void Bullet::InitialVelocity(Vector2 direction) { actualVelocity = { direction.x * velocityModule, direction.y * velocityModule}; }

void Bullet::Draw() { 
    if (destroyed) explosion.Draw();
    else DrawCircle(position.x, position.y, bulletRadius, RED);
}

bool Bullet::HasCollision() {
    bool collision = false;
    MapReader* mapObj = dynamic_cast<MapReader*>(Game::gameObjects[0].get());
    std::vector<MapTile> map = mapObj->GetOptimizedMap();
    std::vector<MapTile> players = std::vector<MapTile>(0);//mapObj->GetPlayers();
    map.insert(map.end(), players.begin(), players.end());
    for (int i = 0; i < map.size(); i++) {
        if (CheckCollisionCircleRec(position, bulletRadius, map[i].GetRectangle())) {
            collision = true;
            break;
        }
    }
    return collision;
}

void Bullet::Explode() {
    explosion = Explosion(position, explosionRadius, explosionMiliseconds);
    destroyed = true;
    MapReader* mapObj = dynamic_cast<MapReader*>(Game::gameObjects[0].get());
    mapObj->DestroyTiles(explosion);
}
