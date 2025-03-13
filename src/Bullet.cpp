#include <raylib.h>
#include "Bullet.h"

void Bullet::Update() {

}

void Bullet::Charging()  {
		
    velocityModule += velocityIncrease;
    return;
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
        
    return;
}

void Bullet::Destroy() {
}
