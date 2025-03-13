#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "raylib.h"  
#include "Aim.h"
#include "Bullet.h"

class Player : public GameObject {
public:
	Aim playerAim;
	Bullet playerLauncherEmpty;
	Bullet playerLauncher;

	float healthPoints;

	bool aiming = true;
	bool charging = false;
	bool isTurn = false;

	Player(Vector2 playerPosition, Vector2 playerSize) : GameObject(playerPosition, playerSize) {
		Vector2 centerPosition = { playerPosition.x + playerSize.x / 2, playerPosition.y + playerSize.y / 2 };
		playerAim = Aim(centerPosition);
		playerLauncher = Bullet(centerPosition);
		playerLauncherEmpty = Bullet(centerPosition);
	}

	void Update() override;
	void Draw() override;
};

#endif