#include "AnimationController.h"

void AnimationController::Update() {
	if (!active) return;
	framesCounter++;

	if (framesCounter >= (60 / framesSpeed))
	{
		framesCounter = 0;
		currentFrame++;

		if (currentFrame > framesInAnimation - 1) currentFrame = 0;

		frameRec.y = (float)currentFrame * (float)texture.height / framesInAnimation;
	}
}

void AnimationController::Draw() {
	if (!active) return;

	Vector2 centeredPosition;
	float offsetX = frameRec.width / 2 - size.x / 2;
	float offsetY = frameRec.height / 2 - size.y / 2;

	if (round)  centeredPosition = { position.x - size.x/2, position.y - size.y/2};
	else centeredPosition = { position.x - offsetX, position.y - offsetY };
	
	DrawTextureRec(texture, frameRec, centeredPosition, WHITE);
}