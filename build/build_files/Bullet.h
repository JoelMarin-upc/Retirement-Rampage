#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "GameObject.h"
#include "raylib.h"  

class Bullet : public GameObject {
public:
    Vector2 missileSize = { 10, 10 };
    Vector2 actualVelocity = { 0, 0 };
    float velocityModule = 0.0f;
    float velocityIncrease = 0.2f;
    float launcherRadius = 10.0f;
    float gravity = 0.1f;

    Bullet() : GameObject() {}
    Bullet(Vector2 center) : GameObject(center, Vector2()) {}

    void Update() override;
    void Charging();
    void Shoot();
    void InitialVelocity(Vector2 direction);
    void Draw() override;
    void Destroy();
};

#endif // LAUNCHER_H
