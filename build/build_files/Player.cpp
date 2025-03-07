#include "Player.h"

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

    if (!charging) playerAim.Update();
    if (!aiming) playerLauncher.Shoot();
}

void Player::Draw() {
    DrawRectangle(position.x, position.y, size.x, size.y, BLUE);
    playerAim.Draw();
    playerLauncher.Draw();
    playerLauncherEmpty.Draw();
}