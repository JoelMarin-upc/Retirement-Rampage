#include "Explosion.h"

Explosion::Explosion() : GameObject(), radius(0), milisecondsToEnd(0), lastTime(0) {}

Explosion::Explosion(Vector2 position, float radius, int milisecondsToEnd) : GameObject(position, Vector2{ radius * 2, radius * 2 }) {
	this->radius = radius;
	this->milisecondsToEnd = milisecondsToEnd;
	lastTime = GetFrameTime() * 1000;
	animation = AnimationController(position, size, "circle50.png", true, true, 8, 12);
}
	
void Explosion::Update() {
	animation.Update();
	lastTime = GetFrameTime() * 1000;
	if (milisecondsToEnd > 0) { milisecondsToEnd -= lastTime; }
	if (milisecondsToEnd <= 0) animation.active = false;
}

void Explosion::Draw() {
	animation.Draw();
}
