#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Explosion.h"
#include "raylib.h"  

class Bullet : public GameObject {
public:
    Vector2 missileSize = { 10, 10 };
    Vector2 actualVelocity = { 0, 0 };
    float velocityModule = 0.0f;
    float velocityIncrease = 0.2f;
    float bulletRadius = 10.0f;
    float explosionRadius = 50.0f;
    int explosionMiliseconds = 600;
    float gravity = 0.1f;
    bool destroyed = false;
    Explosion explosion = Explosion();

    Bullet() : GameObject() {}
    Bullet(Vector2 center) : GameObject(center, Vector2()) {}

    void Update() override;
    void Charging();
    void Shoot();
    void InitialVelocity(Vector2 direction);
    void Draw() override;
    bool HasCollision();
    void Explode();
};

#endif
