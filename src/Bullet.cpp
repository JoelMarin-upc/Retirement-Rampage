#include <raylib.h>
#include "Bullet.h"

void Bullet::Update() {

}

//int barMax = 10;
//int barCounter;
//int barVelocity;

bool Bullet::Charging()  {
		
    velocityModule += velocityIncrease;
    barCounter = velocityModule / barVelocity;
    if (barCounter == 60) {
        barCounter = 0;
        return false;
    }
    std::cout << barCounter;
    return true;
}

void Bullet::Shoot() {
    actualVelocity.y += gravity;
    position.x += actualVelocity.x;
    position.y += actualVelocity.y;
}

void Bullet::InitialVelocity(Vector2 direction) {
    actualVelocity = { direction.x * velocityModule, direction.y * velocityModule};
}

void Bullet::Draw()  {
		
    DrawCircle(position.x, position.y, launcherRadius, RED);
    for (int i = 0; i < barCounter; i++) {
        DrawRectangle(i * barSize.x + barPosition.x, barPosition.y, barSize.x, barSize.y, ORANGE);

    }
        
    return;
}



void Bullet::Destroy() {
}
