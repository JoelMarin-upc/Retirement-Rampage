#include <raylib.h>
//#include "GameObject.cpp"
//#include "Aim.h"

class Aim {
private:
    Vector2 aimingPoint;
    
    Vector2 centerPosition;

public:
    Vector2 vectorDirector = { 1,0 };
	Color color;
	Vector2 crosshairSize = { 10,10 };
    bool facingRight = true;
    float angle = 0;
    float range = 100;


	

	//void Aim::Update() {
	//}

    void InitAim(Vector2 center) {
        centerPosition = center;
    }

	void Update()  {
        if (IsKeyDown(KEY_RIGHT)) {
            facingRight = true;
        }
        if (IsKeyDown(KEY_LEFT)) {
            facingRight = false;
        }
        if (IsKeyDown(KEY_UP) && (vectorDirector.x > 0 || vectorDirector.y > 0)) {
            angle -= 0.025;
            vectorDirector.y = sin(angle);
            vectorDirector.x = cos(angle);
        }
        if (IsKeyDown(KEY_DOWN) && (vectorDirector.x > 0 || vectorDirector.y < 0)) {
            angle += 0.025;
            vectorDirector.y = sin(angle);
            vectorDirector.x = cos(angle);
        }

        if (facingRight) aimingPoint = { centerPosition.x + (vectorDirector.x * range) , centerPosition.y + (vectorDirector.y * range) };
        else  aimingPoint = { centerPosition.x - (vectorDirector.x * range) , centerPosition.y + (vectorDirector.y * range) };
		Draw();
        return;
	}

	void Draw()  {
		
        if (facingRight) DrawRectangle(aimingPoint.x, aimingPoint.y, 10, 10, BLACK);
        else DrawRectangle(aimingPoint.x, aimingPoint.y, crosshairSize.x, crosshairSize.y, BLACK);

	}

	void Destroy() {
	//	aiming = false;
	}
};
