#include "Aim.h"
#include <math.h>

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

}

void Aim::Draw() {
    if (facingRight)
        DrawRectangle(aimingPoint.x, aimingPoint.y, 10, 10, BLACK);
    else
        DrawRectangle(aimingPoint.x, aimingPoint.y, crosshairSize.x, crosshairSize.y, BLACK);
}