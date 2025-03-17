#include "Explosion.h"

Explosion::Explosion() : GameObject(), radius(0), milisecondsToEnd(0), lastTime(0) {}

Explosion::Explosion(Vector2 position, int radius, int milisecondsToEnd) : GameObject(position, Vector2()) {
	this->radius = radius;
	this->milisecondsToEnd = milisecondsToEnd;
	lastTime = GetFrameTime() * 1000;
}
	
void Explosion::Update() {
	lastTime = GetFrameTime() * 1000;
	if (milisecondsToEnd > 0) milisecondsToEnd -= lastTime;
}

void Explosion::Draw() {
	if (milisecondsToEnd > 0) DrawCircle(position.x, position.y, radius, WHITE);
}
