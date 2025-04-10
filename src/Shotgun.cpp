#include <raylib.h>
#include <vector>
#include "Shotgun.h"
#include "Explosion.h"
#include "MapReader.h"
#include "Game.h"

void Shotgun::Update() {
    --distanceMiliseconds;
    if (destroyed) {
        explosion.Update();
        return;
    }
    else if (HasCollision() || distanceMiliseconds < 0) Explode();
    // uses screen size
    else if (position.x > 800 || position.x < 0 || position.y < 0 || position.y >450) destroyed = true;
    else {
        Shoot();
    }
}


void Shotgun::Shoot() {
    position.x += actualVelocity.x;
    position.y += actualVelocity.y;

}

void Shotgun::InitialVelocity(Vector2 direction) { actualVelocity = { direction.x * velocityModule, direction.y * velocityModule}; }

void Shotgun::Draw() {
    if (destroyed) explosion.Draw();
    else if (isProjectileOnAir == true)
    {
        DrawCircle(position.x, position.y, bulletRadius, RED);
    }
}

bool Shotgun::HasCollision() {
    bool collision = false;
    MapReader* mapObj = Game::GetMap();
    std::vector<MapTile> map = mapObj->GetOptimizedMap();
    std::vector<MapTile> players = mapObj->GetPlayers();
    map.insert(map.end(), players.begin(), players.end());
    TurnManager* turnObj = Game::GetTurnManager();
    if (distanceMiliseconds <= playerOutMiliseconds) {
        for (int i = 0;i < turnObj->playerList.size();++i) {
            if (CheckCollisionCircleRec(position, bulletRadius, turnObj->playerList[i]->GetRectangle())) {
                collision = true;
                turnObj->playerList[i]->GetDamaged(position);
                break;
            }
        }
    }
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
    DrawCircle(position.x, position.y, explosionRadius , WHITE);
    destroyed = true;
  //  TurnManager* turnObj = Game::GetTurnManager();
    //turnObj->CheckPlayerHit(explosion);
    //MapReader* mapObj = dynamic_cast<MapReader*>(Game::gameObjects[0].get());
   // mapObj->DestroyTiles(explosion);
}
