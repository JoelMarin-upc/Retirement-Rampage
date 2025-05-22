#include <raylib.h>
#include <vector>
#include "UnderBullet.h"
#include "Explosion.h"
#include "MapReader.h"
#include "Game.h"
#include "SoundEffects.h"

void UnderBullet::Update() {
    if (destroyed) {
        explosion.Update();
        return;
    }

    if (position.x > Game::screenWidth || position.x < 0 || position.y < 0 || position.y > Game::screenHeight) destroyed = true;

    if (HasCollision()) {
        Shoot();
        animation.Update();
    }
    else {

    }
    //uses screen size
    
}

bool UnderBullet::Charging() {
    velocityModule += velocityIncrease;
    barCounter = velocityModule / barVelocity;
    if (barCounter >= maxVelocity) {
        barCounter = 0;
        return false;
    }

    return true;
}

void UnderBullet::Shoot() {
    actualVelocity.y -= gravity;
    actualVelocity.x += wind;
    position.x += actualVelocity.x * GetFrameTime();
    position.y += actualVelocity.y * GetFrameTime();
    animation.position = position;
}

void UnderBullet::InitialVelocity(Vector2 direction) { actualVelocity = { direction.x * velocityModule, direction.y * velocityModule }; }

void UnderBullet::Draw() {
    if (destroyed) explosion.Draw();
    else if (isProjectileOnAir == true)
    {
        /*DrawCircle(position.x, position.y, bulletRadius, RED);*/
        animation.Draw();
    }
    else {
        float lenght = barCounter / 60;
        barPosition = { 40, (float)(Game::screenHeight)-100 };
        for (int i = 0; i < lenght; i++) {
            DrawRectangle(i * barSize.x + barPosition.x, barPosition.y, barSize.x, barSize.y, ORANGE);
        }
        if (lenght > 0) DrawRectangle(maxVelocity / 60 * barSize.x + barPosition.x, barPosition.y, barSize.x * 3, barSize.y, RED);
    }
}

bool UnderBullet::HasCollision() {
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

void UnderBullet::Explode() {
    explosion = Explosion(position, explosionRadius, explosionMiliseconds);
    destroyed = true;
    MapReader* mapObj = Game::GetMap();
    TurnManager* turnObj = Game::GetTurnManager();
    mapObj->DestroyTiles(explosion);
    turnObj->CheckPlayerHit(explosion);

}
