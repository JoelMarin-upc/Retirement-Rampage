#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "raylib.h"  
#include "Aim.h"
#include "Bullet.h"
#include "AnimationController.h"

class Player : public GameObject {
public:
	AnimationController animation;
	Aim playerAim;
	Bullet playerLauncherEmpty;
	Bullet playerLauncher;
	float speed = 0;
	bool aiming = true;
	bool charging = false;

	Player(Vector2 playerPosition, Vector2 playerSize, char* sprite) : GameObject(playerPosition, playerSize) {
		Vector2 centerPosition = { playerPosition.x + playerSize.x / 2, playerPosition.y + playerSize.y / 2 };
		animation = AnimationController(position, size, sprite, true, false, 36, 12);
		playerAim = Aim(centerPosition);
		playerLauncher = Bullet(centerPosition);
		playerLauncherEmpty = Bullet(centerPosition);
	}

	void Update() override;
	void Draw() override;
	void MoveY(int ammount, bool add);
	void Fall();
	Rectangle GetFloorCollider();
};

#endif