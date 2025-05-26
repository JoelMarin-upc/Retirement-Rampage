#ifndef UNDERBULLET_H
#define UNDERBULLET_H

#include "GameObject.h"
#include "Explosion.h"
#include "raylib.h"  
#include "AnimationController.h"
#include <vector>
#include <iostream>

class UnderBullet : public GameObject {
public:
    AnimationController animation;
    Vector2 missileSize = { 10, 10 };
    Vector2 actualVelocity = { 0, 0 };
    float velocityModule = 0.0f;
    float velocityIncrease = 15;
    int maxVelocity = 6000;
    float bulletRadius = 10.0f;
    float explosionRadius = 50.0f;
    int explosionMiliseconds = 600;
    float gravity = 20;
    bool destroyed = false;
    bool isProjectileOnAir = false;
    bool enteredGround = false;

    Explosion explosion = Explosion();

    int barMax = 40;
    int barCounter = 0;
    float barVelocity = 0.3;
    Vector2 barSize = { 4,20 };
    Vector2 barPosition = { 400,400 };

    UnderBullet() : GameObject() {}
    UnderBullet(Vector2 center) : GameObject(center, Vector2()) {
        animation = AnimationController(position, size, "sheepfal.png", true, false, 32, 35);
    }

    void Update() override;
    bool Charging();
    void Shoot();
    void InitialVelocity(Vector2 direction);
    void Draw() override;
    bool HasCollision();
    void Explode();
};

#endif
