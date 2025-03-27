#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"
#include "raylib.h"
#include "AnimationController.h"

class Explosion : public GameObject {
private:
    int milisecondsToEnd;
    int lastTime;

public:
    float radius;
    AnimationController animation;

    Explosion();

    Explosion(Vector2 position, float radius, int milisecondsToEnd);

    void Update() override;

    void Draw() override;
};

#endif

