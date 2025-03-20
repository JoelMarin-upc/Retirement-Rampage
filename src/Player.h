#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "raylib.h"  
#include "Aim.h"
#include "Bullet.h"
#include "Shotgun.h"
#include "SoundEffects.h"
#include <string> 
#include <map>
#include <iostream>



class Player : public GameObject {
public:
	Aim playerAim;
	Bullet playerLauncherEmpty;
	Bullet playerLauncher;
	Shotgun playerShotgunEmpty;
	Shotgun playerShotgun;
	float speed = 0;
	bool aiming = true;
	bool charging = false;
	//falta añadir una variable que detecte cuando hay un disparo en el aire y no es turno de nadie

	int healthPoints = 100;
	std::string healthString = "100";
	bool isTurn = false;

	std::string currentWeapon = "bullet";



	Player(Vector2 playerPosition, Vector2 playerSize) : GameObject(playerPosition, playerSize) {
		Vector2 centerPosition = { playerPosition.x + playerSize.x / 2, playerPosition.y + playerSize.y / 2 };
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