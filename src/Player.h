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
#include <cmath>
#include "AnimationController.h"
#include "WeaponsHUD.h"
#include "SoundEffects.h"

class Player : public GameObject {
public:
	AnimationController animation;
	Aim playerAim;
	Bullet playerLauncherEmpty;
	Bullet playerLauncher;
	Shotgun playerShotgunEmpty;
	Shotgun playerShotgun;
	WeaponsHUD PlayerHud;
	SoundEffects PlayerSounds;
	float speed = 0;
	int playerNum;
	bool aiming = false;
	bool charging = false;
	bool dead = false;
	bool isActive = false;
	bool teleportActive = true;
	bool HUDactive = false;


	int healthPoints = 100;
	std::string healthString = "100";
	bool isTurn = false;

	std::string currentWeapon = "none";

	Player() : GameObject() {}

	Player(int playerNum, Vector2 playerPosition, Vector2 playerSize) : GameObject(playerPosition, playerSize), playerNum(playerNum) {
		type = "player";
		Vector2 centerPosition = { playerPosition.x + playerSize.x / 2, playerPosition.y + playerSize.y / 2 };
		animation = AnimationController(position, size, "scarfy.png", true, false, 36, 12);
		playerAim = Aim(centerPosition);
		playerLauncherEmpty = Bullet(centerPosition);
		playerShotgunEmpty = Shotgun(centerPosition);
	}

	void Update() override;
	void Draw() override;
	void Move(Vector2 ammount, bool add);
	void MoveX(int ammount, bool add);
	void MoveY(int ammount, bool add);
	void Fall();
	void BulletEquipped();
	void ShotgunEquipped();
	void TeleportEquipped();
	Rectangle GetFloorCollider();
	void GetDamaged(Vector2 pos);
};

#endif