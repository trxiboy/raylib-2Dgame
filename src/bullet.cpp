// Libraries:
#include <raylib.h>

#include <algorithm>
#include <iostream>
#include <cmath>

#include "calculations.h"

#include "bullet.h"
#include "window.h"


// Bullet Class Functions:
bool Bullet::Fire(Window *window) {
    bulletPos = LerpPosition(startPos, endPos, moveToFactor);
    DrawTextureEx(bulletSprite, bulletPos, 0.0f, window->worldScale/6, WHITE);

    if (moveToFactor >= 1.0f) {
        moveToFactor = 1.0f;
        //UnloadTexture(bulletSprite);
        return true;
    } else {
        moveToFactor += 1.0f * 10.0f / Distance(startPos, endPos);
        return false;
    }
}