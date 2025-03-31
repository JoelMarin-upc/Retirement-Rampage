#include "GameObject.h"

GameObject::GameObject() : position({ 0, 0 }), size({ 0, 0 }) { }

GameObject::GameObject(Vector2 position, Vector2 size) : position(position), size(size) { }

void GameObject::Init() { }

Rectangle GameObject::GetRectangle() { return { position.x, position.y, size.x, size.y }; }

Vector2 GameObject::GetCenter() { return { position.x + size.x / 2, position.y + size.y / 2 }; }