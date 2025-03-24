#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "GameObject.h"

class AnimationController : public GameObject {
public:
	bool active;
	bool round;
	Texture2D texture;
	Rectangle frameRec;
	int currentFrame = 0;
	int framesCounter = 0;
	int framesSpeed;
	int framesInAnimation;

	AnimationController() : GameObject(), active(false), round(false), texture({}), frameRec({}), framesInAnimation(0), framesSpeed(0) {}

	AnimationController(Vector2 pos, Vector2 size, char* file, bool active, bool round, int framesInAnimation, int framesSpeed) : GameObject(pos, size), active(active), round(round), framesInAnimation(framesInAnimation), framesSpeed(framesSpeed) {
		texture = LoadTexture(file);
		frameRec = { 0.0f, 0.0f, (float)texture.height / framesInAnimation, (float)texture.width };
	}

	void Update() override;

	void Draw() override;
};

#endif