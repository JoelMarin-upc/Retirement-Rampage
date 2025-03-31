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
    
    //Vector2 missileSize = { 10, 10 };
    Vector2 actualVelocity = { 0, 0 };
    float velocityModule = 15;
    float bulletRadius = 3.0f;
    float explosionRadius = 10.0f;
    int explosionMiliseconds = 400;;
    bool destroyed = false;
    bool isPorjectileOnAir = false;

    Explosion explosion = Explosion();
    
    Shotgun() : GameObject() {}
    Shotgun(Vector2 center) : GameObject(center, Vector2()) {}
    
    void Shotgun::Update() override;
    void Shoot();
    void InitialVelocity(Vector2 direction);
    void Shotgun::Draw() override;
    bool HasCollision();
    void Explode();
};

#endif