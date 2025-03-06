#include <raylib.h>
//#include "GameObject.cpp"
//#include "Bullet.h"

class Launcher {
private:
    float distance = 30;
    Vector2 position;

public:
	Color color;
    Vector2 endPosition;
    float launcherRadius = 10;


	

    void Update() {

    }

    void InitShotgun(Vector2 center) {
        position = center;
    }



    void CalculateShot(Vector2 direction) {
        endPosition=position + direction*distance;   
        Draw();
    }

	void Draw()  {
		
        DrawLine(position, endPosition, RED);
        
        return;
	}

	void Destroy() {
	}
};
