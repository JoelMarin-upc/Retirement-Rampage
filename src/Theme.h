#ifndef THEME_H
#define THEME_H

#include "raylib.h"  
#include <string>

class Theme {
public:
	Rectangle sourceRec;
	Rectangle destRec;

	Theme() {}
	Theme(std::string path) {
		LoadTextures(path);
	}
	std::string name;
	Texture2D background;
	Color dirtTile;
	Color grassTile;
	void LoadTextures(std::string dirPath);
	void DrawBackground();
};

#endif