#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "raylib.h"  
#include "Aim.h"
#include "Bullet.h"
#include "Shotgun.h"
#include <string> 
#include <map>
#include <iostream>
#include "AnimationController.h"

class Player : public GameObject {
public:
	AnimationController animation;
	Aim playerAim;
	Bullet playerLauncherEmpty;
	Bullet playerLauncher;
	Shotgun playerShotgunEmpty;
	Shotgun playerShotgun;
	float speed = 0;
	int playerNum;
	bool aiming = true;
	bool charging = false;

	int healthPoints = 100;
	std::string healthString = "100";
	bool isTurn = false;

	std::string currentWeapon = "bullet";

	Player() : GameObject() {}

	Player(int playerNum, Vector2 playerPosition, Vector2 playerSize) : GameObject(playerPosition, playerSize), playerNum(playerNum) {
		Vector2 centerPosition = { playerPosition.x + playerSize.x / 2, playerPosition.y + playerSize.y / 2 };
		animation = AnimationController(position, size, "scarfy.png", true, false, 36, 12);
		playerAim = Aim(centerPosition);
		playerLauncher = Bullet(centerPosition);
		playerLauncherEmpty = Bullet(centerPosition);
		playerShotgunEmpty = Shotgun(centerPosition);
		playerShotgun = Shotgun(centerPosition);
	}

	void Update() override;
	void Draw() override;
	void MoveY(int ammount, bool add);
	void Fall();
	void BulletEquipped();
	void ShotgunEquipped();
	Rectangle GetFloorCollider();
};

#endif