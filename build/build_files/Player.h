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

	bool aiming = true;
	bool charging = false;

	Player(Vector2 playerPosition, Vector2 playerSize) : GameObject(playerPosition, playerSize) {
		playerAim = Aim(playerPosition);
		playerLauncher = Bullet(playerPosition);
		playerLauncherEmpty = Bullet(playerPosition);
	}

	void Update() override;
	void Draw() override;
};

#endif