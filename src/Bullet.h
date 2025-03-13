#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "raylib.h"  
#include <vector>
#include <iostream>



class Bullet : public GameObject {
public:
    Vector2 missileSize = { 10, 10 };
    Vector2 actualVelocity = { 0, 0 };
    int barMax = 40;
    int barCounter = 0;
    float barVelocity = 0.5;
    Vector2 barSize = { 4,20 };
    Vector2 barPosition = {400,400 };
    //vector<GameObject> bars;
    float velocityModule = 0.0f;
    float velocityIncrease = 0.15f;
    float launcherRadius = 10.0f;
    float gravity = 0.1f;

    Bullet() : GameObject() {}
    Bullet(Vector2 center) : GameObject(center, Vector2()) {}

    void Update() override;
    bool Charging();
    void Shoot();
    void InitialVelocity(Vector2 direction);
    void Draw() override;
    void DrawCharge();

    void Destroy();
};

#endif
