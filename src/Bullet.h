#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Explosion.h"
#include "raylib.h"  
#include <vector>
#include <iostream>

class Bullet : public GameObject {
public:
    Vector2 missileSize = { 10, 10 };
    Vector2 actualVelocity = { 0, 0 };
    float velocityModule = 0.0f;
    float velocityIncrease = 0.15f;
    float bulletRadius = 10.0f;
    float explosionRadius = 50.0f;
    int explosionMiliseconds = 600;
    float gravity = 0.25f;
    bool destroyed = false;
    bool isPorjectileOnAir = false;

    Explosion explosion = Explosion();

    int barMax = 40;
    int barCounter = 0;
    float barVelocity = 0.3;
    Vector2 barSize = { 4,20 };
    Vector2 barPosition = { 400,400 };

    Bullet() : GameObject() {}
    Bullet(Vector2 center) : GameObject(center, Vector2()) {}

    void Update() override;
    bool Charging();
    void Shoot();
    void InitialVelocity(Vector2 direction);
    void Draw() override;
    bool HasCollision();
    void Explode();
};

#endif
