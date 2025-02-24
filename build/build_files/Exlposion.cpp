#include "GameObject.cpp"

class Explosion : public GameObject {
	int radius;
	int milisecondsToEnd;
	int lastTime;

public:
	Explosion(Vector2 position, int radius, int milisecondsToEnd) : GameObject(position, Vector2()) {
		this->radius = radius;
		this->milisecondsToEnd = milisecondsToEnd;
		lastTime = GetTime() * 1000;
	}
	
	void Update() override {
		if (milisecondsToEnd > 0) milisecondsToEnd -= lastTime;
	}

	void Draw() override {
		if (milisecondsToEnd > 0) DrawCircle(position.x, position.y, radius, WHITE);
	}
};