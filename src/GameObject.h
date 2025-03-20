#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <raylib.h>
#include "SoundEffects.h"

class GameObject {
public:
    Vector2 position, size;

    GameObject();

    GameObject(Vector2 position, Vector2 size);

    virtual void Init();

    virtual void Update() = 0;

    virtual void Draw() = 0;

    Rectangle GetRectangle();

    Vector2 GetCenter();
};

#endif
