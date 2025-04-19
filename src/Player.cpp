#include "Player.h"
#include "MapReader.h"
#include "Game.h"

#define G 0.1

void Player::Update() {
    //if (IsKeyDown(KEY_ENTER)) {
      //  isTurn = true;
      //  playerAim.isTurn = true;
   // }
    if (isTurn){
        if (IsKeyDown(KEY_ONE)) {
            currentWeapon = "bullet";
            aiming = true;
            charging = false;
            playerAim.isTurn = true;

        }
        if (IsKeyDown(KEY_TWO)) {
            currentWeapon = "shotgun";
            aiming = true;
            charging = false;
            playerAim.isTurn = true;
        }
        if (IsKeyDown(KEY_THREE) && teleportActive) {
            currentWeapon = "teleport";
            aiming = false;
            charging = false;
            playerAim.isTurn = false;
        }
    }

    if (currentWeapon == "bullet") BulletEquipped();
    else if (currentWeapon == "shotgun") ShotgunEquipped();
    else if (currentWeapon == "teleport") TeleportEquipped();
    else if (currentWeapon == "none") {
        aiming = false;
        charging = false;
        playerAim.isTurn = false;

    }

    Fall();

    healthString = std::to_string(healthPoints);

    animation.position = position;
    animation.Update();
    if (!charging) playerAim.Update();
    //if (!aiming) playerLauncher.Update();

    //std::cout << playerLauncher.isProjectileOnAir;;

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
            playerLauncher.isProjectileOnAir = true;
            SoundEffects i;
            i.playsfx(3);
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
    if (!isTurn && playerLauncher.destroyed) isActive = false;
}


void  Player::ShotgunEquipped() {
    if (isTurn) {
        if (IsKeyReleased(KEY_SPACE)) {
            if (!charging) {
                SoundEffects i;
                i.playsfx(2);
                playerShotgun = playerShotgunEmpty;
                playerShotgun.isProjectileOnAir = true;
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
        if (playerShotgun.destroyed == false) charging = false;
    }
    if (!isTurn && playerShotgun.destroyed) isActive = false;

}


void  Player::TeleportEquipped() {
    DrawRectangle(GetMouseX()-15, GetMouseY()-15, 30, 30, BLACK);
    if (IsKeyReleased(KEY_SPACE)) {
        position.x = GetMouseX() - 15;
        position.y = GetMouseY() - 15;
        playerAim.position.x = GetMouseX() - 15;
        playerAim.position.y = GetMouseY() - 15;
        teleportActive = false;

        currentWeapon = "bullet";
        aiming = true;
        charging = false;
        playerAim.isTurn = true;

        playerLauncherEmpty.position.x = position.x+size.x/2;
        playerLauncherEmpty.position.y = position.y + size.y / 2;
        playerShotgunEmpty.position.x = position.x + size.x / 2;
        playerShotgunEmpty.position.y = position.y + size.y / 2;
    }
}

void Player::Move(Vector2 ammount, bool add) {
    MoveX(ammount.x, add);
    MoveY(ammount.y, add);
}

void Player::MoveX(int ammount, bool add) {
    if (add) {
        position.x += ammount;
        playerAim.position.x += ammount;
        playerLauncher.position.x += ammount;
        playerLauncherEmpty.position.x += ammount;
        playerShotgun.position.x += ammount;
        playerShotgunEmpty.position.x += ammount;
    }
    else {
        position.x = ammount;
        playerAim.position.x = ammount;
        playerLauncher.position.x = ammount;
        playerLauncherEmpty.position.x = ammount;
        playerShotgun.position.x = ammount;
        playerShotgunEmpty.position.x = ammount;
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
    //if (currentWeapon == "bullet" && playerLauncher.isisProjectileOnAir) playerLauncher.Draw();
    //shotgun is not in the object list
    if (currentWeapon == "shotgun")playerShotgun.Draw();
        const char* cstr = healthString.c_str();
        DrawText(cstr, position.x, position.y - 30, 20, WHITE); //needs to use global position
        if (isTurn) {
            const char* cstr2 = currentWeapon.c_str();
            DrawText(cstr2, 400, 20, 20, WHITE);
            DrawTriangle({ position.x,position.y - size.y*2}, {position.x + (size.x / 2),position.y - size.y}, {position.x + size.x,position.y - size.y * 2 }, YELLOW);
        }
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

void Player::GetDamaged(Vector2 pos) {
    int damage = 100-(abs(pos.x - (position.x+size.x/2)) + abs(pos.y - (position.y+size.y / 2)));
    std::cout<<(abs(pos.x - (position.x + size.x / 2)) + abs(pos.y - (position.y + size.y /2)));
    damage *= 0.5;
    healthPoints = healthPoints - damage;
    if (healthPoints<=0) dead = true;

}