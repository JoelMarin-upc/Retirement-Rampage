#include "Player.h"
#include "MapReader.h"
#include "Game.h"

#define G 9.81

void Player::Update() {
    //if (IsKeyDown(KEY_ENTER)) {
      //  isTurn = true;
      //  playerAim.isTurn = true;
   // }

    if (isTurn){
        if (generateWind) {
            wind = (rand() % (20 - 0 + 1) + 0) - 10;
            generateWind = false;
        }
        if (IsKeyDown(KEY_ZERO)) {
            currentWeapon = "underBullet";
            aiming = true;
            charging = false;
            playerAim.isTurn = true;

        }
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
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            HUDactive = true;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (HUDactive == true) {
                if (PlayerHud.CheckBox() == 1) {
                    currentWeapon = "bullet";
                    aiming = true;
                    charging = false;
                    playerAim.isTurn = true;
                }
                else if (PlayerHud.CheckBox() == 2) {
                    currentWeapon = "shotgun";
                    aiming = true;
                    charging = false;
                    playerAim.isTurn = true;
                }
                else if (PlayerHud.CheckBox() == 3) {
                    currentWeapon = "teleport";
                    aiming = false;
                    charging = false;
                    playerAim.isTurn = false;
                }
                HUDactive = false;
            }
        }

    }

    if (!isTurn) {
        HUDactive = false;
    }

    if (currentWeapon == "underBullet") underBulletEquipped();
    else if (currentWeapon == "bullet") BulletEquipped();
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
    PlayerHud.changeImg(1);

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
            playerLauncher.wind = wind;
            playerLauncher.isProjectileOnAir = true;
            PlayerSounds.playsfx(1);
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


void  Player::underBulletEquipped() {
    PlayerHud.changeImg(1);

    if (isTurn) {
        if (IsKeyDown(KEY_SPACE)) {
            if (!charging) {
                aiming = true;
                charging = true;
                playerUnderBullet = playerUnderBulletEmpty;
            }
            if (!playerUnderBullet.Charging()) charging = false;
        }
        if (IsKeyReleased(KEY_SPACE) || (IsKeyDown(KEY_SPACE) && !charging)) {
            playerUnderBullet.isProjectileOnAir = true;
            PlayerSounds.playsfx(1);
            aiming = false;
            charging = false;
            isTurn = false;
            playerAim.isTurn = false;
            if (playerAim.facingRight)playerUnderBullet.InitialVelocity(playerAim.vectorDirector);
            else playerUnderBullet.InitialVelocity({ -playerAim.vectorDirector.x, playerAim.vectorDirector.y });
        }
        if (!charging) playerAim.Update();
    }
    if (!aiming) playerUnderBullet.Update();
    if (!isTurn && playerUnderBullet.destroyed) isActive = false;
}


void  Player::ShotgunEquipped() {
    PlayerHud.changeImg(2);

    if (isTurn) {
        if (IsKeyReleased(KEY_SPACE)) {
            if (!charging) {
                PlayerSounds.playsfx(2);
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
    PlayerHud.changeImg(3);

    DrawRectangle(GetMouseX()-15, GetMouseY()-15, 30, 30, BLACK);
    if (IsKeyReleased(KEY_SPACE)) {
        PlayerSounds.playsfx(4); //plays teleport sfx
        position.x = GetMouseX() - 15;
        position.y = GetMouseY() - 15;
        playerAim.position.x = GetMouseX() - 15;
        playerAim.position.y = GetMouseY() - 15;
        teleportActive = false;

        currentWeapon = "bullet";
        aiming = true;
        charging = false;
        playerAim.isTurn = true;

        playerUnderBulletEmpty.position.x = position.x + size.x / 2;
        playerLauncherEmpty.position.x = position.x+size.x/2;
        playerShotgunEmpty.position.y = position.y + size.y / 2;
    }
}

void Player::Move(Vector2 ammount, bool add) {
    MoveX(ammount.x, add);
    MoveY(ammount.y, add);
}

void Player::MoveX(int ammount, bool add) {
    ammount *= GetFrameTime();

    if (add) {
        position.x += ammount;
        playerAim.position.x += ammount;
        playerUnderBullet.position.x += ammount;
        playerUnderBulletEmpty.position.x += ammount;
        playerLauncher.position.x += ammount;
        playerLauncherEmpty.position.x += ammount;
        playerShotgun.position.x += ammount;
        playerShotgunEmpty.position.x += ammount;
    }
    else {
        position.x = ammount;
        playerAim.position.x = ammount;
        playerUnderBullet.position.x = ammount;
        playerUnderBulletEmpty.position.x = ammount;
        playerLauncher.position.x = ammount;
        playerLauncherEmpty.position.x = ammount;
        playerShotgun.position.x = ammount;
        playerShotgunEmpty.position.x = ammount;
    }
}

void Player::MoveY(int ammount, bool add) {
    ammount *= GetFrameTime();

    if (add) {
        position.y += ammount;
        playerAim.position.y += ammount;
        playerUnderBullet.position.y += ammount;
        playerUnderBulletEmpty.position.y += ammount;
        playerLauncher.position.y += ammount;
        playerLauncherEmpty.position.y += ammount;
        playerShotgun.position.y += ammount;
        playerShotgunEmpty.position.y += ammount;
    }
    else {
        position.y = ammount;
        playerAim.position.y = ammount;
        playerUnderBullet.position.y = ammount;
        playerUnderBulletEmpty.position.y = ammount;
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
    if (currentWeapon == "underBullet")playerUnderBullet.Draw();
    const char* cstr = healthString.c_str();
    DrawText(cstr, position.x, position.y - 30, 20, WHITE);
    if (isTurn) {
        DrawRectangle(1500 - 10, (float)(Game::screenHeight)-100, 20, 20, BLACK);
        if (wind > 0) DrawRectangle(1500, (float)(Game::screenHeight)-100, wind * 20, 20, BLUE);     
        else DrawRectangle(1500 + (wind * 20), (float)(Game::screenHeight)-100, -wind * 20, 20, BLUE);

        const char* cstr2 = currentWeapon.c_str();
        DrawText(cstr2, 45, (float)(Game::screenHeight)-100, 20, WHITE);
        DrawTriangle({ position.x,position.y - size.y*2}, {position.x + (size.x / 2),position.y - size.y}, {position.x + size.x,position.y - size.y * 2 }, YELLOW);
    }
    // DIBUJAR COLLIDER
    //Rectangle r = GetFloorCollider();
    //DrawRectangle(r.x, r.y, r.width, r.height, YELLOW);
    //DrawRectangle(position.x, position.y, size.x, size.y, BLUE);

    //Weapon HUD trigger
    if (HUDactive == true) {
        PlayerHud.DrawSprite();
        PlayerHud.HUDmove();
    }

    if (HUDactive == false) {
        PlayerHud.DrawSprite();
        PlayerHud.HUDretract();
    }
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
            ResetWeapons();


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

void Player::ResetWeapons() {
    playerAim.position = position;
    playerUnderBulletEmpty.position = position;
    playerLauncherEmpty.position = position;
    playerShotgunEmpty.position = position;
}



void Player::GetDamaged(Vector2 pos) {
    int damage = 100-(abs(pos.x - (position.x+size.x/2)) + abs(pos.y - (position.y+size.y / 2)));
    //std::cout<<(abs(pos.x - (position.x + size.x / 2)) + abs(pos.y - (position.y + size.y /2)));
    damage *= 0.5;
    healthPoints = healthPoints - damage;
    if (healthPoints<=0) dead = true;

}