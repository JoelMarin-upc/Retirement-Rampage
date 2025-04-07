#include "Player.h"
#include "MapReader.h"
#include "Game.h"

#define G 0.1

void Player::Update() {
    //if (IsKeyDown(KEY_ENTER)) {
      //  isTurn = true;
      //  playerAim.isTurn = true;
   // }
    if (IsKeyDown(KEY_ONE)) {
        currentWeapon = "bullet";
        aiming = true;
        charging = false;
    }
    if (IsKeyDown(KEY_TWO)) {
        currentWeapon = "shotgun";
        aiming = true;
        charging = false;
    }
    if (currentWeapon == "bullet") BulletEquipped();
    else if (currentWeapon == "shotgun") ShotgunEquipped();

    Fall();

    healthString = std::to_string(healthPoints);

    animation.position = position;
    animation.Update();
    if (!charging) playerAim.Update();
    //if (!aiming) playerLauncher.Update();
}


void  Player::BulletEquipped() {
    if (isTurn) {
        if (IsKeyDown(KEY_SPACE)) {
            if (!charging) {
                aiming = true;
                charging = true;
                playerLauncher = playerLauncherEmpty;
            }
            if (!playerLauncher.Charging()) charging = false;
        }
        if (IsKeyReleased(KEY_SPACE) || (IsKeyDown(KEY_SPACE) && !charging)) {
            SoundEffects i;
            i.playsfx(3);
            playerLauncher.isPorjectileOnAir = true;
            aiming = false;
            charging = false;
            isTurn = false;
            playerAim.isTurn = false;
            if (playerAim.facingRight)playerLauncher.InitialVelocity(playerAim.vectorDirector);
            else playerLauncher.InitialVelocity({ -playerAim.vectorDirector.x, playerAim.vectorDirector.y });
        }
        if (!charging) playerAim.Update();
    }
    if (!aiming) playerLauncher.Update();
}


void  Player::ShotgunEquipped() {
    if (isTurn) {
        if (IsKeyPressed(KEY_SPACE)) {
            if (!charging) {
                SoundEffects i;
                i.playsfx(2);
                playerShotgun = playerShotgunEmpty;
                playerShotgun.isPorjectileOnAir = true;
                aiming = false;
                charging = true;
                isTurn = false;
                playerAim.isTurn = false;
                if (playerAim.facingRight)playerShotgun.InitialVelocity(playerAim.vectorDirector);
                else playerShotgun.InitialVelocity({ -playerAim.vectorDirector.x, playerAim.vectorDirector.y });
            }
        }
        if (!charging) playerAim.Update();
    }
    if (!aiming) {
        playerShotgun.Update();
        if (playerLauncher.destroyed == false) charging = false;
    }
}



void Player::MoveY(int ammount, bool add) {
    if (add) {
        position.y += ammount;
        playerAim.position.y += ammount;
        playerLauncher.position.y += ammount;
        playerLauncherEmpty.position.y += ammount;
        playerShotgun.position.y += ammount;
        playerShotgunEmpty.position.y += ammount;
    }
    else {
        position.y = ammount;
        playerAim.position.y = ammount;
        playerLauncher.position.y = ammount;
        playerLauncherEmpty.position.y = ammount;
        playerShotgun.position.y = ammount;
        playerShotgunEmpty.position.y = ammount;
    }
}

void Player::Draw() {
    animation.Draw();
    playerAim.Draw();
    playerLauncher.Draw();
    //if (currentWeapon == "bullet" && playerLauncher.isPorjectileOnAir) playerLauncher.Draw();
    //shotgun is not in the object list
    if (currentWeapon == "shotgun")playerShotgun.Draw();
    const char* cstr = healthString.c_str();
    DrawText(cstr, position.x, position.y - 30, 20, WHITE);
    const char* cstr2 = currentWeapon.c_str();
    DrawText(cstr2, 100, 400, 20, WHITE);
    // DIBUJAR COLLIDER
    //Rectangle r = GetFloorCollider();
    //DrawRectangle(r.x, r.y, r.width, r.height, YELLOW);
    //DrawRectangle(position.x, position.y, size.x, size.y, BLUE);
}

Rectangle Player::GetFloorCollider() {
    return { position.x+(size.x/3), position.y + (size.y/2), size.x/3, size.y / 2 };
}

void Player::Fall() {
    MapReader* mapObj = Game::GetMap();
    std::vector<MapTile> map = mapObj->GetOptimizedMap();

    bool hitObstacle = false;
    float fallSpeed = speed;

    for (int i = 0; i < map.size(); i++) {
        Rectangle floorRect = map[i].GetRectangle();

        if (CheckCollisionRecs(floorRect, this->GetFloorCollider())) {
            hitObstacle = true;
            speed = 0;

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

    if (position.y >= Game::bottomY) dead = true;
}