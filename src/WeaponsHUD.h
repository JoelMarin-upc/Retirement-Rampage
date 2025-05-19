#ifndef WEAPONSHUD_H
#define WEAPONSHUD_H

#include "GameObject.h"



class WeaponsHUD {
private:
	int RectSizeX = 100;
	int RectSizeY = 100;
	int NumOfWeapons = 3;
	float middleOfScreen = GetScreenWidth() / 2.0f - static_cast <float> (RectSizeX)*NumOfWeapons / 2.0f;

	Texture2D Granade;
	Texture2D Shotgun;
	Texture2D Teleporter;

	Rectangle boxA = { middleOfScreen, static_cast <float> (-RectSizeY) , static_cast <float> (RectSizeX)*NumOfWeapons, static_cast <float> (RectSizeY) }; //creates rectangle

	int SpriteY = -RectSizeY;


public:

	// loads all the images
	void ReloadImgs() {
		Image GranadeImg = LoadImage("Granade_Icon.png");
		Image ShotgunImg = LoadImage("Shotgun_Icon.png");
		Image TeleporterImg = LoadImage("Teleporter_Icon.png");
		Granade = LoadTextureFromImage(GranadeImg);
		Shotgun = LoadTextureFromImage(ShotgunImg);
		Teleporter = LoadTextureFromImage(TeleporterImg);
		UnloadImage(GranadeImg);
		UnloadImage(ShotgunImg);
		UnloadImage(TeleporterImg);
	}

	WeaponsHUD() {
		ReloadImgs();
	}

	//code for the draw loop
	void DrawSprite() {
		DrawRectangleRec(boxA, BLACK);
		DrawTexture(Granade, middleOfScreen, SpriteY, WHITE);
		DrawTexture(Shotgun, middleOfScreen+ RectSizeX, SpriteY, WHITE);
		DrawTexture(Teleporter, middleOfScreen + RectSizeX *2, SpriteY, WHITE);
	}

	// moves the HUD downwards until it's fully visible on the screen
	void HUDmove() {
		if (boxA.y < 0) {
			boxA.y += 5;
			SpriteY += 5;
		}
	}

	// moves the HUD upwards until it's not visible on the screen
	void HUDretract() {
		if (boxA.y > -RectSizeY) {
			boxA.y -= 5;
			SpriteY -= 5;
		}
	}

	void CheckClickHUD() {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			DrawSprite();
		}
	}

	//This will change the icon's image to indicate the currently selected weapon
	//everytime it will reload the images to bring them to their original state
	/*
	1 = bullet
	2 = shotgun
	3 = teleport
	*/
	void changeImg(int i) {

		ReloadImgs();

		if (i == 1) {
			Image GranadeImg = LoadImage("Granade_Icon_SELSECTED.png");
			Granade = LoadTextureFromImage(GranadeImg);
			UnloadImage(GranadeImg);
		}
		if (i == 2) {
			Image ShotgunImg = LoadImage("Shotgun_Icon_SELECTED.png");
			Shotgun = LoadTextureFromImage(ShotgunImg);
			UnloadImage(ShotgunImg);
		}
		if (i == 3) {
			Image TeleporterImg = LoadImage("Teleporter_Icon_SELECTED.png");
			Teleporter = LoadTextureFromImage(TeleporterImg);
			UnloadImage(TeleporterImg);
		}

	}

	// dpending on mouse position it will return a weapon number
	int CheckBox() {
		ReloadImgs();
		if (GetMousePosition().x > middleOfScreen && GetMousePosition().x < middleOfScreen + RectSizeX * 1 && GetMousePosition().y > -middleOfScreen && GetMousePosition().y > -middleOfScreen + RectSizeY) {
			return 1;
		}
		if (GetMousePosition().x > middleOfScreen && GetMousePosition().x < middleOfScreen + RectSizeX * 2 && GetMousePosition().y > -middleOfScreen && GetMousePosition().y > -middleOfScreen + RectSizeY) {
			return 2;
		}
		if (GetMousePosition().x > middleOfScreen && GetMousePosition().x < middleOfScreen + RectSizeX * 3 && GetMousePosition().y > -middleOfScreen && GetMousePosition().y > -middleOfScreen + RectSizeY) {
			return 3;
		}
	}
};

#endif