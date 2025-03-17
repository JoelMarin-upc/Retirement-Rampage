#include "Player.h"
#include "MapReader.h"
#include "Game.h"

#define G 0.1

void Player::Update() {
    if (IsKeyDown(KEY_SPACE)) {
        if (!charging) {
            aiming = true;
            charging = true;
            playerLauncher = playerLauncherEmpty;
        }
        playerLauncher.Charging();
    }

    if (IsKeyReleased(KEY_SPACE)) {
        aiming = false;
        charging = false;
        if (playerAim.facingRight)playerLauncher.InitialVelocity(playerAim.vectorDirector);
        else playerLauncher.InitialVelocity({ -playerAim.vectorDirector.x, playerAim.vectorDirector.y });
    }

    Fall();

    if (!charging) playerAim.Update();
    if (!aiming) playerLauncher.Update();
}

void Player::MoveY(int ammount, bool add) {
    if (add) {
        position.y += ammount;
        playerAim.position.y += ammount;
        playerLauncher.position.y += ammount;
        playerLauncherEmpty.position.y += ammount;
    }
    else {
        position.y = ammount;
        playerAim.position.y = ammount;
        playerLauncher.position.y = ammount;
        playerLauncherEmpty.position.y = ammount;
    }
}

void Player::Draw() {
    DrawRectangle(position.x, position.y, size.x, size.y, BLUE);
    playerAim.Draw();
    playerLauncher.Draw();
    // DIBUJAR COLLIDER
    //Rectangle r = GetFloorCollider();
    //DrawRectangle(r.x, r.y, r.width, r.height, YELLOW);
}

Rectangle Player::GetFloorCollider() {
    return {position.x+(size.x/3), position.y + (size.y/2), size.x/3, size.y / 2};
}

void Player::Fall() {
    MapReader* mapObj = dynamic_cast<MapReader*>(Game::gameObjects[0].get());
    std::vector<MapTile> map = mapObj->GetOptimizedMap();

    bool hitObstacle = false;
    float fallSpeed = speed;

    for (int i = 0; i < map.size(); i++) {
        Rectangle floorRect = map[i].GetRectangle();

        if (CheckCollisionRecs(floorRect, this->GetFloorCollider())) {
            hitObstacle = true;

            if (position.y + size.y / 2 > floorRect.y) {
                MoveY(floorRect.y - size.y, false);
                speed = 0;
            }
            break;
        }
    }

    if (!hitObstacle) {
        MoveY(fallSpeed, true);  
        speed += G;  
    }
}