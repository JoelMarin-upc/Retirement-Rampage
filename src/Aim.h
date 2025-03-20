#ifndef AIM_H
#define AIM_H

#include "GameObject.h"
#include "SoundEffects.h"


class Aim : public GameObject {
private:
    Vector2 aimingPoint;

public:
    Vector2 vectorDirector = { 1, 0 };
    Vector2 crosshairSize = { 10, 10 };
    bool facingRight = true;
    float angle = 0;
    float range = 100;
    bool isTurn = false;

    Aim() : GameObject(), aimingPoint({ 0,0 }) {}
    Aim(Vector2 center) : GameObject(center, Vector2()), aimingPoint({0,0}) {}
    void Update() override;
    void Draw() override;
};

#endif // AIM_H
