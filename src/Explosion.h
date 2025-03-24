#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"
#include "raylib.h"

class Explosion : public GameObject {
private:
    int milisecondsToEnd;
    int lastTime;

public:
    int radius;

    Explosion();

    Explosion(Vector2 position, int radius, int milisecondsToEnd);

    void Update() override;

    void Draw() override;
};

#endif

