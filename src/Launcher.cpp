#include <raylib.h>
//#include "GameObject.cpp"
//#include "Bullet.h"

class Launcher {
private:
    Vector2 vectorDirector;
    Vector2 position;

public:
	Color color;
	Vector2 missileSize = { 10,10 };
    Vector2 actualVelocity = { 0,0 };
    float velocityModule;
    float velocityIncrease = 0.2;
    float launcherRadius = 10;
    float gravity = 0.1;


	



    void InitLauncher(Vector2 center) {
        position = center;
    }

	void Charging()  {
		
        velocityModule += velocityIncrease;

        return;
	}

    void Shoot() {
        
        actualVelocity.y += gravity;
        position.x += actualVelocity.x;
        position.y += actualVelocity.y;
        Draw();
    }

    void InitialVelocity(Vector2 direction) {
        vectorDirector = direction;
        actualVelocity = {vectorDirector.x * velocityModule, vectorDirector.y* velocityModule};
    }
	void Draw()  {
		
       DrawCircle(position.x, position.y, launcherRadius, RED);
        
        return;
	}

	void Destroy() {
	}
};
