#pragma once
#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include "raylib.h" 
#include <iostream>
#include <map>
using namespace std;

class SoundEffects {
public:

	void playsfx(int name) {
		if (name == 1) {
			Sound Explosion = LoadSound("Explosion.wav");
			PlaySound(Explosion);
		}
		else if (name == 2) {
			Sound Shotgun = LoadSound("Shotgun.wav");
			PlaySound(Shotgun);
		}
		else if (name == 3) {
			Sound Bazooka = LoadSound("Bazooka.wav");
			PlaySound(Bazooka);
		}
	}

};

#endif