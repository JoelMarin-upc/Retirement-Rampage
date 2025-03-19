#include "GameObject.h"

GameObject::GameObject() {
    position = Vector2();
    position.x = 0;
    position.y = 0;

    size = Vector2();
    size.x = 0;
    size.y = 0;
}

GameObject::GameObject(Vector2 position, Vector2 size) {
    this->position = position;
    this->size = size;
}

void GameObject::Init() {
}

Rectangle GameObject::GetRectangle() {
    return { position.x, position.y, size.x, size.y };
}

Vector2 GameObject::GetCenter() {
    return { position.x + size.x / 2, position.y + size.y / 2 };
}