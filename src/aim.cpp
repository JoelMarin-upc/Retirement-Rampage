#include "Aim.h"
#include <math.h>
#include <raylib.h>

void Aim::Update() {
    if (IsKeyDown(KEY_RIGHT)) {
        facingRight = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        facingRight = false;
    }
    if (IsKeyDown(KEY_UP) && (vectorDirector.x > 0 || vectorDirector.y > 0)) {
        angle -= 0.025;
        vectorDirector.y = sin(angle);
        vectorDirector.x = cos(angle);
    }
    if (IsKeyDown(KEY_DOWN) && (vectorDirector.x > 0 || vectorDirector.y < 0)) {
        angle += 0.025;
        vectorDirector.y = sin(angle);
        vectorDirector.x = cos(angle);
    }

    if (facingRight)
        aimingPoint = { position.x + (vectorDirector.x * range), position.y + (vectorDirector.y * range) };
    else
        aimingPoint = { position.x - (vectorDirector.x * range), position.y + (vectorDirector.y * range) };

    animation.Update();
    animation.position = { aimingPoint.x, aimingPoint.y };

}

void Aim::Draw() {
    if (isTurn) {
        if (facingRight) {
            animation.Draw();
        }
        else {
            animation.Draw();
        }
    }
}