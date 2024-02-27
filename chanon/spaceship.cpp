#include "spaceship.hpp"

Spaceship::Spaceship()
{
    
    laserSound = LoadSound("Sounds/laser.ogg"); //[Add Sounds]
}

Spaceship::~Spaceship() {
    
    UnloadSound(laserSound); //[Add Sounds]
}

void Spaceship::FireLaser()

    if(GetTime() - lastFireTime >= 0.35) {
        PlaySound(laserSound);//[Add Sounds]เสียงตอนยิงทำงานเมื่อกดยิง
    }
}
