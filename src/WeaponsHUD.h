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

	Rectangle boxA = { middleOfScreen, static_cast <float> (-RectSizeY) , static_cast <float> (RectSizeX)*NumOfWeapons, static_cast <float> (RectSizeY) };

	int SpriteY = -RectSizeY;

public:
	int CheckBox() {
		if (GetMousePosition().x > middleOfScreen && GetMousePosition().x < middleOfScreen + RectSizeX * 1 && GetMousePosition().y > -middleOfScreen && GetMousePosition().y > -middleOfScreen + RectSizeY) {
			return 1;
		}
		if (GetMousePosition().x > middleOfScreen && GetMousePosition().x < middleOfScreen + RectSizeX * 2 && GetMousePosition().y > -middleOfScreen && GetMousePosition().y > -middleOfScreen + RectSizeY) {
			return 2;
		}
		if (GetMousePosition().x > middleOfScreen && GetMousePosition().x < middleOfScreen+RectSizeX * 3 && GetMousePosition().y > -middleOfScreen && GetMousePosition().y > -middleOfScreen + RectSizeY) {
			return 3;
		}
	}

	WeaponsHUD() {
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

	void DrawSprite() {
		DrawRectangleRec(boxA, BLACK);
		DrawTexture(Granade, middleOfScreen, SpriteY, WHITE);
		DrawTexture(Shotgun, middleOfScreen+ RectSizeX, SpriteY, WHITE);
		DrawTexture(Teleporter, middleOfScreen + RectSizeX *2, SpriteY, WHITE);

	}

	void HUDmove() {
		if (boxA.y < 0) {
			boxA.y += 5;
			SpriteY += 5;
		}
	}

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

};

#endif