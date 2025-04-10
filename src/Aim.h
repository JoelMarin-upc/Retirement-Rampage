#ifndef AIM_H
#define AIM_H

#include "GameObject.h"
#include "AnimationController.h"


class Aim : public GameObject {
private:
    Vector2 aimingPoint;

public:
    Vector2 vectorDirector = { 1, 0 };
    Vector2 crosshairSize = { 3, 3 };
    AnimationController animation;
    bool facingRight = true;
    float angle = 0;
    float range = 100;
    bool isTurn = false;

    Aim() : GameObject(), aimingPoint({ 0,0 }) {}
    Aim(Vector2 center) : GameObject(center, Vector2()), aimingPoint({ 0,0 }) {
        animation = AnimationController(aimingPoint, crosshairSize, "markerr.png", true, false, 10, 15);
    }
    void Update() override;
    void Draw() override;
};

#endif // AIM_H
