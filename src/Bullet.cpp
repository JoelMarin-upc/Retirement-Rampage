#include <raylib.h>
#include <vector>
#include "Bullet.h"
#include "Explosion.h"
#include "MapReader.h"
#include "Game.h"
#include "SoundEffects.h"

void Bullet::Update() {
    if (destroyed) {
        explosion.Update();
        return;
    }
    if (HasCollision()) Explode();
    //uses screen size
    else if (position.x > Game::screenWidth || position.x < 0 || position.y < 0|| position.y > Game::screenHeight) destroyed = true;
    else Shoot();
    animation.Update();
}

bool Bullet::Charging() {
    velocityModule += velocityIncrease;
    barCounter = velocityModule / barVelocity;
    if (barCounter == 60) {
        barCounter = 0;
        return false;
    }

    return true;
}

void Bullet::Shoot() {
    actualVelocity.y += gravity;
    position.x += actualVelocity.x;
    position.y += actualVelocity.y;
    animation.position = position;
}

void Bullet::InitialVelocity(Vector2 direction) { actualVelocity = { direction.x * velocityModule, direction.y * velocityModule }; }

void Bullet::Draw() {
    if (destroyed) explosion.Draw();
    else if (isProjectileOnAir == true)
    {
        /*DrawCircle(position.x, position.y, bulletRadius, RED);*/
        animation.Draw();
    }
    else {
        for (int i = 0; i < barCounter; i++) {            
            barPosition = { 40, (float)(Game::screenHeight)-100 };
            DrawRectangle(i * barSize.x + barPosition.x, barPosition.y, barSize.x, barSize.y, ORANGE);
        }
    }
}

bool Bullet::HasCollision() {
    bool collision = false;
    MapReader* mapObj = Game::GetMap();
    std::vector<MapTile> map = mapObj->GetOptimizedMap();
    //buscar posiciones players
    //std::vector<MapTile> players = mapObj->GetPlayers();
    //map.insert(map.end(), players.begin(), players.end());
    for (int i = 0; i < map.size(); i++) {
        if (CheckCollisionCircleRec(position, bulletRadius * 0.8f, map[i].GetRectangle())) {
            collision = true;
            break;
        }
    }
    return collision;
}

void Bullet::Explode() {
    explosion = Explosion(position, explosionRadius, explosionMiliseconds);
    destroyed = true;
    MapReader* mapObj = Game::GetMap();
    TurnManager* turnObj = Game::GetTurnManager();
    mapObj->DestroyTiles(explosion);
    turnObj->CheckPlayerHit(explosion);

}
