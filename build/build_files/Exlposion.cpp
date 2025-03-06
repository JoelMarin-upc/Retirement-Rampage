#include "Explosion.h"

Explosion::Explosion(Vector2 position, int radius, int milisecondsToEnd) : GameObject(position, Vector2()) {
	this->radius = radius;
	this->milisecondsToEnd = milisecondsToEnd;
	lastTime = GetTime() * 1000;
}
	
void Explosion::Update() {
	if (milisecondsToEnd > 0) milisecondsToEnd -= lastTime;
}

void Explosion::Draw() {
	if (milisecondsToEnd > 0) DrawCircle(position.x, position.y, radius, WHITE);
}
