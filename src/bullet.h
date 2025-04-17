// Libraries:
#include <raylib.h>

#include <algorithm>
#include <iostream>
#include <cmath>

#include "calculations.h"

#include "window.h"


// Bullet Class:
class Bullet{
    public:
        Bullet(Vector2 start, Vector2 end) {
            startPos = start; endPos = end;

            bulletSprite = LoadTexture("../resources/sprites/bullet.png");
        }
        
        bool Fire(Window *window);

    private:
        Vector2 bulletPos{ 0, 0 };
        Vector2 startPos, endPos;
        float moveToFactor = 0;

        // Sprite Variables:
        Texture2D bulletSprite;
};
