#include "Theme.h"
#include <fstream>
#include <Game.h>

void Theme::LoadTextures(std::string dirPath) {
	background = LoadTexture((dirPath+"/background.png").c_str());
    std::ifstream file((dirPath + "/colors.txt").c_str());
    std::string str;

    int r1, g1, b1;
    if (file >> r1 >> g1 >> b1) {
        dirtTile = Color { (unsigned char)r1, (unsigned char)g1, (unsigned char)b1, 255 };
    }

    int r2, g2, b2;
    if (file >> r2 >> g2 >> b2) {
        grassTile = Color { (unsigned char)r2, (unsigned char)g2, (unsigned char)b2, 255 };
    }

    float scale = (float)Game::screenHeight / background.height;
    float scaledWidth = background.width * scale;

    sourceRec = { 0, 0, (float)background.width, (float)background.height };
    destRec = { (Game::screenWidth - scaledWidth) / 2.0f, 0, scaledWidth, (float)Game::screenHeight };

}

void Theme::DrawBackground() {
    DrawTexturePro(background, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
}