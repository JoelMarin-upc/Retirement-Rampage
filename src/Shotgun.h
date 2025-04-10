#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "GameObject.h"
#include "Explosion.h"
#include "raylib.h"  
#include "SoundEffects.h"
#include <vector>
#include <iostream>

class Shotgun : public GameObject {
public:
    AnimationController animation;
    //Vector2 missileSize = { 10, 10 };
    Vector2 actualVelocity = { 0, 0 };
    float velocityModule = 15;
    float bulletRadius = 3.0f;
    float explosionRadius = 10.0f;
    int explosionMiliseconds = 400;
    int playerOutMiliseconds = 12;
    int distanceMiliseconds = 15;
    bool destroyed = false;
    bool isProjectileOnAir = false;

    Explosion explosion = Explosion();
    
    Shotgun() : GameObject() {}
    Shotgun(Vector2 center) : GameObject(center, Vector2()) {
        animation = AnimationController(position, size, "bullet.png", true, false, 32, 120);
    }
    
    void Shotgun::Update() override;
    void Shoot();
    void InitialVelocity(Vector2 direction);
    void Shotgun::Draw() override;
    bool HasCollision();
    void Explode();
};

#endif