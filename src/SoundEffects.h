#pragma once
#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include "raylib.h" 
#include <iostream>
#include <map>
using namespace std;

class SoundEffects {
private:
	Sound Explosion;
	Sound Shotgun;
	Sound Bazooka;
	Sound Teleport;

public:

	//loads sfx
	SoundEffects() {
		Explosion = LoadSound("Explosion.wav");
		Shotgun = LoadSound("Shotgun.wav");
		Bazooka = LoadSound("Bazooka.wav");
		Teleport = LoadSound("Teleport.wav");
	}

	//plays sfx
	void playsfx(int name) {
		if (name == 1) {
			PlaySound(Explosion);
		}
		else if (name == 2) {
			PlaySound(Shotgun);
		}
		else if (name == 3) {
			PlaySound(Bazooka);
		}
		else if (name == 4){
			PlaySound(Teleport);
		}
	}

};

#endif