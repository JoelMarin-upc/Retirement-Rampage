#include <raylib.h>
#include <vector>
#include "Shotgun.h"
#include "Explosion.h"
#include "MapReader.h"
#include "Game.h"
#include "SoundEffects.h"

void Shotgun::Update() {
    if (destroyed) {
        explosion.Update();
        return;
    }
    else if (HasCollision()) Explode();
    // uses screen size
    else if (position.x > 800 || position.x < 0 || position.y < 0 || position.y >450) destroyed = true;
    else {
        Shoot();
    }
    animation.Update();
}


void Shotgun::Shoot() {
    position.x += actualVelocity.x;
    position.y += actualVelocity.y;
    animation.position = position;
}

void Shotgun::InitialVelocity(Vector2 direction) { actualVelocity = { direction.x * velocityModule, direction.y * velocityModule}; }

void Shotgun::Draw() {
    if (destroyed) explosion.Draw();
    else if (isPorjectileOnAir == true)
    {
        animation.Draw();
    }
}

bool Shotgun::HasCollision() {
    bool collision = false;
    MapReader* mapObj = Game::GetMap();
    std::vector<MapTile> map = mapObj->GetOptimizedMap();
    std::vector<MapTile> players = mapObj->GetPlayers();
    map.insert(map.end(), players.begin(), players.end());
    for (int i = 0; i < map.size(); i++) {
        if (CheckCollisionCircleRec(position, bulletRadius, map[i].GetRectangle())) {
            collision = true;
            break;
        }
    }
    return collision;
}

void Shotgun::Explode() {
    //explosion = Explosion(position, explosionRadius, explosionMiliseconds);
    destroyed = true;
    std::cout << "destroy";
    //MapReader* mapObj = dynamic_cast<MapReader*>(Game::gameObjects[0].get());
   // mapObj->DestroyTiles(explosion);
}
