#ifndef WEAPONSHUD_H
#define WEAPONSHUD_H

#include "GameObject.h"

class WeaponsHUD {
private:
	Texture2D Granade;

public:

	WeaponsHUD() {
		Image GranadeImg = LoadImage("Granade_Icon.png");
		Granade = LoadTextureFromImage(GranadeImg);
		UnloadImage(GranadeImg);
	}

	void DrawSprite() {
		DrawRectangle(430, -30, 500, 500, BLACK);
		DrawTexture(Granade, 430, -30, WHITE);
	}

	int CheckClickHUD() {
		if ()
	}

};

#endif