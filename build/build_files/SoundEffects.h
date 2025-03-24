#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include "raylib.h" 
#include <iostream>
#include <map>
using namespace std;

class SoundEffects {
public:
	
	

	/*static map<string, Sound> m;*/

	/*static void loadsounds() {
		Sound Explosion = LoadSound("resources/Sound Effects/Explosion.wav");
		Sound Shotgun = LoadSound("resources/Sound Effects/Shotgun.wav");

		m.insert({ "Explosion", Explosion });
		m.insert({ "Shotgun", Shotgun });
	}*/

	/*static void playsound(string name) {
		PlaySound(m.at(name));
	}*/

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